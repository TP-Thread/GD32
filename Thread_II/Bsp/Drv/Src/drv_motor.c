/**
 * @file drv_motor.c
 * @author A-rtos (A-rtos@outlook.com)
 * @brief 电机驱动相关函数
 * @version 0.1 搭建工程
 * @version 0.2 基于Index脉冲的机械零点对齐校准编码器
 * @date 2026-01-30
 *
 * @copyright Copyright (c) 2026 A-rtos
 *
 */

#include "drv_motor.h"

MotorCtrl_t MC;

/**
 * @brief 电机系统参数初始化
 */
void motor_init(void)
{
    MC.Motor.RunState = CURRENT_CALIB; // 设置电机最初的运行状态
    MC.Motor.RunMode = ENCODER_CALIB;  // 设置电机最初的运行模式

    MC.Identify.CurMax = 0.6f; // 设置电阻电感识别时的最大母线电流（单位：安）

    MC.Sample.CurrentDir = 1;                 // 设置电机电流采样的方向(由硬件决定)
    MC.Sample.CurrentFactor = CURRENT_FACTOR; // 相电流计算系数(由采样电阻值和放大倍数以及ADC分辨率计算得出)
    MC.Sample.BusFactor = VBUS_FACTOR;        // 母线电压计算系数（由分压电阻计算得出）

    MC.Encoder.Dir = CCW;               // 设置编码器的方向（逆时针转动 角度从0向360度增加）
    MC.Encoder.PolePairs = POLEPAIRS;   // 设置电机的极对数（磁铁数除以2）
    MC.Encoder.EncoderValMax = PUL_MAX; // 设置编码器单圈脉冲的最大值4095

    MC.Encoder.IndexDetected = 0; // Index脉冲检测标志清零

    MC.Foc.IdLPFFactor = 0.1f;   // 设置d轴电流低通滤波系数
    MC.Foc.IqLPFFactor = 0.1f;   // 设置q轴电流低通滤波系数
    MC.Foc.PwmCycle = PWM_CYCLE; // 设置PWM周期
    MC.Foc.PwmLimit = PWM_LIMLT; // 设置PWM限幅值

    MC.Position.ElectricalValMax = PUL_MAX; // 设置编码器单圈脉冲的最大值

    MC.TAccDec.AccSpeed = ACCELERATION; // 设置速度模式下的加速度

    MC.Speed.ElectricalValMax = PUL_MAX;       // 设置编码器单圈脉冲的最大值
    MC.Speed.ElectricalSpeedLPFFactor = 0.05f; // 设置速度低通滤波系数
    MC.Speed.ElectricalSpeedFactor = 146.5f;   // 设置速度计算系数

    MC.IqPid.Kp = 0.2f;   // 设置q轴PID比例系数
    MC.IqPid.Ki = 0.002f; // 设置q轴PID比例系数
    MC.IqPid.OutMax = 6;  // 设置q轴PID输出上限初始值，限制Uq，后续设置为Ubus/√3
    MC.IqPid.OutMin = -6; // 设置q轴PID输出下限初始值，限制Uq，后续设置为Ubus/√3

    MC.IdPid.Kp = 0.2f;   // 设置d轴PID比例系数
    MC.IdPid.Ki = 0.002f; // 设置d轴PID比例系数
    MC.IdPid.OutMax = 6;  // 设置d轴PID输出上限初始值，限制Ud，后续设置为Ubus/√3
    MC.IdPid.OutMin = -6; // 设置d轴PID输出下限初始值，限制Ud，后续设置为Ubus/√3

    MC.SpdPid.Kp = 0.001f;    // 设置速度PID比例系数
    MC.SpdPid.KpMax = 0.005f; // 设置速度PID比例系数最大值（用于分段或模糊PID）
    MC.SpdPid.KpMin = 0.001f; // 设置速度PID比例系数最小值（用于分段或模糊PID）
    MC.SpdPid.Ki = 0.000002f; // 设置速度PID积分系数
    MC.SpdPid.OutMax = 8;     // 设置速度PID输出上限,4006电机适配40A电调，IqPid.Ref限制为单相最大电流/√3
    MC.SpdPid.OutMin = -8;    // 设置速度PID输出下限

    MC.PosPid.Kp = 0.5f;       // 设置位置PID比例系数
    MC.PosPid.Ki = 0;          // 设置位置PID积分系数
    MC.PosPid.Kd = 0;          // 设置位置PID微分系数
    MC.PosPid.OutMax = 14000;  // 设置位置PID输出上限
    MC.PosPid.OutMin = -14000; // 设置位置PID输出下限
}

/********************************************************************************
 * 电机参数辨识
 *******************************************************************************/
/**
 * @brief 电机参数辨识，向电机施加特定电压和电流，测算出电机的相电阻（Rs）和相电感（Ls）
 *        两点法测电阻和阶跃响应法测电感
 */
void motor_identify(void)
{
    switch (MC.Identify.State)
    {
    case RESISTANCE_IDENTIFICATION: // 电阻识别
    {
        if (MC.Identify.Flag == 0) // 清空参数
        {
            MC.Foc.Uq = 0;
            MC.Foc.Ud = 0;
            MC.Identify.Count = 0;
            MC.Identify.WaitTim = 0;
            MC.Identify.Flag = 1;
        }

        if (MC.Identify.Flag == 1)
        {
            if ((MC.Sample.IuReal * MC.Foc.Ud * 1.5f) / MC.Sample.BusReal >= 0.6f * MC.Identify.CurMax)
            {
                MC.Identify.Flag = 2;
            }
            else
            {
                MC.Foc.Ud += 0.0001f; // 逐渐增加电流（过大电机发热，过小测量不准）
                MC.Identify.VoltageSet[0] = MC.Foc.Ud;
            }
        }

        if (MC.Identify.Flag == 2)
        {
            MC.Identify.WaitTim++;
            if (MC.Identify.WaitTim > 4000) // 0.2S 等待电流稳定
            {
                MC.Identify.CurSum += MC.Sample.IuReal;
            }

            if (MC.Identify.WaitTim >= 4100) // 记录100次电流值
            {
                MC.Identify.CurAverage[0] = MC.Identify.CurSum * 0.01f; // 计算平均电流
                MC.Identify.WaitTim = 0;
                MC.Identify.CurSum = 0;
                MC.Identify.Flag = 3;
            }
        }

        if (MC.Identify.Flag == 3)
        {
            if ((MC.Sample.IuReal * MC.Foc.Ud * 1.5f) / MC.Sample.BusReal >= MC.Identify.CurMax)
            {
                MC.Identify.Flag = 4;
            }
            else
            {
                MC.Foc.Ud += 0.0001f; // 逐渐增加电流（过大电机发热，过小测量不准）
                MC.Identify.VoltageSet[1] = MC.Foc.Ud;
            }
        }

        if (MC.Identify.Flag == 4)
        {
            MC.Identify.WaitTim++;
            if (MC.Identify.WaitTim > 4000) // 0.2S 等待电流稳定
            {
                MC.Identify.CurSum += MC.Sample.IuReal;
            }

            if (MC.Identify.WaitTim >= 4100) // 记录100次电流值
            {
                MC.Identify.CurAverage[1] = MC.Identify.CurSum * 0.01f; // 计算平均电流
                MC.Identify.WaitTim = 0;
                MC.Identify.CurSum = 0;
                MC.Identify.Flag = 5;
            }
        }

        if (MC.Identify.Flag == 5)
        {
            MC.Identify.Rs = (MC.Identify.VoltageSet[1] - MC.Identify.VoltageSet[0]) / (MC.Identify.CurAverage[1] - MC.Identify.CurAverage[0]);
            MC.Foc.Ud = 0;
            MC.Identify.Flag = 0;
            MC.Identify.State = INDUCTANCE_IDENTIFICATION;
        }

        MC.Foc.SinVal = 0; // 电角度为0，正弦值为0
        MC.Foc.CosVal = 1; // 电角度为0，余弦值为1
        park_inv_transform(&MC.Foc);
    }
    break;
    case INDUCTANCE_IDENTIFICATION: // 电感识别
    {
        if (MC.Identify.Flag == 0)
        {
            MC.Foc.Uq = 0;
            MC.Foc.Ud = 0;
            if (MC.Sample.IuReal >= -0.05f && MC.Sample.IuReal <= 0.05f)
            {
                MC.Identify.Flag = 1;
            }
        }

        if (MC.Identify.Flag == 1)
        {
            MC.Foc.Ud = MC.Identify.VoltageSet[1];
            MC.Identify.WaitTim++;
            if (MC.Sample.IuReal >= MC.Identify.CurAverage[1] * 0.95f)
            {
                MC.Identify.LsSum += MC.Identify.Rs * 0.334f * 0.00005f * MC.Identify.WaitTim;
                MC.Identify.WaitTim = 0;
                MC.Identify.Count++;
                MC.Identify.Flag = 0;
                MC.Foc.Ud = 0;
                if (MC.Identify.Count >= 100)
                {
                    MC.Identify.Flag = 2;
                }
            }
        }

        if (MC.Identify.Flag == 2)
        {
            MC.Identify.Ls = MC.Identify.LsSum * 0.01f;
            MC.Identify.Ld = MC.Identify.Ls;
            MC.Identify.Lq = MC.Identify.Ls;

            MC.Identify.Flag = 0;
            MC.Identify.LsSum = 0;
            MC.Identify.WaitTim = 0;
            MC.Identify.State = RESISTANCE_IDENTIFICATION;
            MC.Identify.EndFlag = 1;
        }

        MC.Foc.SinVal = 0; // 电角度为0，正弦值为0
        MC.Foc.CosVal = 1; // 电角度为0，余弦值为1
        park_inv_transform(&MC.Foc);
    }
    break;
    }

    MC.Foc.Ubus = MC.Sample.BusReal;
    svpwm_calculate(&MC.Foc);
}

/********************************************************************************
 * 相电流和母线电压计算
 *******************************************************************************/
/**
 * @brief 获取相电流和总线电压基准值
 */
void current_offset_calculate(Sample_t *p)
{
    if (p->OffsetCnt == 0)
    {
        p->EndFlag = 0;
        p->IuOffset = 0;
        p->IwOffset = 0;
        p->BusOffset = 0;
        p->OffsetCnt = 0;
    }

    if (p->OffsetCnt < 1024) // 采集1024次数据求平均值
    {
        p->IuOffset += p->IuRaw;
        p->IwOffset += p->IwRaw;
        p->BusOffset += p->BusRaw;
        p->OffsetCnt++;
    }
    else
    {
        p->IuOffset = p->IuOffset >> 10; // U相电流偏置值
        p->IwOffset = p->IwOffset >> 10; // W相电流偏置值
        p->BusOffset = p->BusOffset >> 10;
        p->BusCalibReal = p->BusOffset * p->BusFactor; // 母线电压真实值(校准值，静态)
        p->OffsetCnt = 0;
        p->EndFlag = 1; // 相电流校准完成标志MC.Sample.EndFlag
    }
}

/**
 * @brief 计算三相电流值，以流入中性点的方向为正
 */
void current_calculate(Sample_t *p)
{
    p->IuReal = p->CurrentDir * (p->IuRaw - p->IuOffset) * p->CurrentFactor;
    p->IwReal = p->CurrentDir * (p->IwRaw - p->IwOffset) * p->CurrentFactor;
    p->IvReal = -p->IuReal - p->IwReal;
}

/**
 * @brief 计算母线电压值
 */
void voltage_calculate(Sample_t *p)
{
    p->BusReal = p->BusRaw * p->BusFactor; // 母线电压真实值(动态)MC.Sample.BusReal
    p->BusChange = p->BusReal - p->BusCalibReal;
}

/********************************************************************************
 * 电角度计算
 *******************************************************************************/
/**
 * @brief 电角度发生器，根据设定的电角速度速度生成电角度
 */
void eangle_generator(Encoder_t *p)
{
    p->ElectricalValSet += (0.00005f * p->ElectricalSpdSet * 0.01666f * p->EncoderValMax); // 根据设定速度 计算电角度值
    if (p->ElectricalValSet >= p->EncoderValMax)                                           // 越过编码器边界点
    {
        p->ElectricalValSet = p->ElectricalValSet - p->EncoderValMax;
    }

    if (p->ElectricalValSet < 0) // 越过编码器边界点
    {
        p->ElectricalValSet = p->ElectricalValSet + p->EncoderValMax;
    }
}

/**
 * @brief 将编码器数据转换为电角度
 */
void eangle_calculate(Encoder_t *p)
{
    if (p->Dir == 1) // 判断编码器方向
    {
        p->EncoderVal = p->EncoderValMax - p->EncoderVal; // 方向取反
    }

    /* 将编码器的机械角度转换为FOC控制所需的电角度 */
    p->ElectricalVal = ((p->EncoderVal - p->CalibOffset) * p->PolePairs) % p->EncoderValMax;

    if (p->ElectricalVal < 0) // 处理校准可能带来的负值
    {
        p->ElectricalVal = p->ElectricalVal + p->EncoderValMax;
    }
}

/********************************************************************************
 * 位置和速度计算
 *******************************************************************************/
/**
 * @brief 计算位置
 */
void position_calculate(Position_t *p)
{
    p->ElectricalPosChange = p->ElectricalPosThis - p->ElectricalPosLast; // 计算单位时间内位移
    p->ElectricalPosLast = p->ElectricalPosThis;

    if (p->ElectricalPosChange >= (p->ElectricalValMax * 0.5f)) // 越过编码器零点
    {
        p->ElectricalPosChange = p->ElectricalPosChange - p->ElectricalValMax;
    }

    if (p->ElectricalPosChange <= (-p->ElectricalValMax * 0.5f)) // 越过编码器零点
    {
        p->ElectricalPosChange = p->ElectricalPosChange + p->ElectricalValMax;
    }

    p->ElectricalPosSum = p->ElectricalPosSum + p->ElectricalPosChange; // 计算总位置
}

/**
 * @brief 计算速度
 */
void speed_calculate(Speed_t *p)
{
    p->ElectricalPosChange = p->ElectricalPosThis - p->ElectricalPosLast; // 计算单位时间内位移
    p->ElectricalPosLast = p->ElectricalPosThis;

    if (p->ElectricalPosChange >= (p->ElectricalValMax * 0.5f)) // 越过编码器零点
    {
        p->ElectricalPosChange = p->ElectricalPosChange - p->ElectricalValMax;
    }

    if (p->ElectricalPosChange <= (-p->ElectricalValMax * 0.5f))
    {
        p->ElectricalPosChange = p->ElectricalPosChange + p->ElectricalValMax; // 越过编码器零点
    }

    p->ElectricalSpeedRaw = p->ElectricalPosChange * p->ElectricalSpeedFactor; // 计算原始电角速度
}

/**
 * @brief T形加减速算法，用于生成平滑的速度轨迹，避免速度突变导致的电流冲击和机械振动
 */
void tshape_acc_dec(Tshape_t *p)
{
    if (p->FinishFlag == 0)
    {
        if ((p->EndSpeed - p->StartSpeed) > 0)
        {
            p->SumSpeed = p->SumSpeed + p->AccSpeed;   // 累加速度
            p->SpeedOut = p->StartSpeed + p->SumSpeed; // 计算输出速度

            if (p->SpeedOut >= p->EndSpeed)
            {
                p->SpeedOut = p->EndSpeed; // 限幅
                p->FinishFlag = 1;         // 达到目标速度，标记完成
            }
        }

        if ((p->EndSpeed - p->StartSpeed) < 0)
        {
            p->SumSpeed = p->SumSpeed - p->AccSpeed;   // 递减速度
            p->SpeedOut = p->StartSpeed + p->SumSpeed; // 计算输出速度

            if (p->SpeedOut <= p->EndSpeed)
            {
                p->SpeedOut = p->EndSpeed;
                p->FinishFlag = 1; // 达到目标速度，标记完成
            }
        }

        if (p->FinishFlag == 1)
        {
            p->SumSpeed = 0;
        }
    }
}

/********************************************************************************
 * 电机控制
 *******************************************************************************/
/**
 * @brief 电机控制，更新电机运行参数
 */
void motor_ctrl()
{
    if (MC.Sample.EndFlag == 1) // 相电流校准后执行
    {
        current_calculate(&MC.Sample); // 计算三相电流值
        voltage_calculate(&MC.Sample); // 计算母线电压值

        /* dq轴电压输出上限，母线电压除以根号3，理论上d轴和q轴电压最大值不能超过这个值，否则SVPWM无法实现 */
        MC.IdPid.OutMax = MC.Sample.BusReal * 0.57735f;
        MC.IdPid.OutMin = -MC.Sample.BusReal * 0.57735f;
        MC.IqPid.OutMax = MC.Sample.BusReal * 0.57735f;
        MC.IqPid.OutMin = -MC.Sample.BusReal * 0.57735f;

        if (MC.Sample.BusReal <= 10 || MC.Sample.BusReal >= 40)
        {
            MC.Motor.RunState = MOTOR_ERROR; // 供电不正常
        }
    }

    /* 状态机 */
    switch (MC.Motor.RunState)
    {
    case CURRENT_CALIB: // 相电流校准
    {
        current_offset_calculate(&MC.Sample);
        if (MC.Sample.EndFlag == 1)
        {
            MC.Motor.RunState = MOTOR_IDENTIFY;
        }
    }
    break;
    case MOTOR_IDENTIFY: // 参数辨识
    {
        motor_identify(); // 测算电机的相电阻和相电感，用于无感控制
        if (MC.Identify.EndFlag == 1)
        {
            MC.Motor.RunState = MOTOR_SENSORUSE;
        }
    }
    break;
    case MOTOR_SENSORUSE: // 有感控制
    {
        sensoruse_ctrl();
    }
    break;
    case MOTOR_SENSORLESS: // 无感控制
    {
        sensorless_ctrl();
    }
    break;
    case MOTOR_ERROR:
    {
        MC.Foc.DutyCycleA = 0;
        MC.Foc.DutyCycleB = 0;
        MC.Foc.DutyCycleC = 0;
    }
    break;
    case MOTOR_STOP:
    {
        MC.Foc.DutyCycleA = 0;
        MC.Foc.DutyCycleB = 0;
        MC.Foc.DutyCycleC = 0;
    }
    break;
    default:
        break;
    }
}

/**
 * @brief 有感控制
 */
void sensoruse_ctrl(void)
{
    /* 计算电角度 */
    eangle_calculate(&MC.Encoder);
    angle_calculate(MC.Encoder.ElectricalVal, &MC.Foc.SinVal, &MC.Foc.CosVal);

    /* 状态机 */
    switch (MC.Motor.RunMode)
    {
    case ENCODER_CALIB: // 编码器校准（基于Index脉冲的机械零点对齐）
    {
        if (MC.Encoder.CalibFlag == 0) // 第一阶段：定位到90度
        {
            MC.Foc.Ud += 0.0001f; // 缓慢增加d轴电压
            MC.Foc.Uq = 0;        // q轴电压为0
            MC.Foc.SinVal = 1;    // 强制电角度90°
            MC.Foc.CosVal = 0;

            if (MC.Foc.Ud >= MC.Identify.VoltageSet[1]) // 校准用的电压与参数识别时一致
            {
                MC.Foc.Ud = 0;
                MC.Encoder.IndexDetected = 0;
                MC.Encoder.CalibFlag = 1;
            }
        }

        if (MC.Encoder.CalibFlag == 1) // 第二阶段：缓慢旋转寻找机械零点
        {
            MC.Foc.Uq = 0.5f;                                                                      // 施加q轴电压
            MC.Encoder.ElectricalSpdSet = 50;                                                      // 设置较低的开环转速
            eangle_generator(&MC.Encoder);                                                         // 生成递增的电角度
            angle_calculate((int32_t)MC.Encoder.ElectricalValSet, &MC.Foc.SinVal, &MC.Foc.CosVal); // 计算sin/cos值

            if (MC.Encoder.IndexDetected) // 检测Index脉冲
            {
                MC.Foc.Uq = 0;
                MC.Encoder.ElectricalSpdSet = 0;
                MC.Encoder.ElectricalValSet = 0;
                MC.Encoder.CalibFlag = 2;
            }
        }

        if (MC.Encoder.CalibFlag == 2) // 第三阶段：定位到电角度0度
        {
            MC.Foc.Ud += 0.0001f;
            MC.Foc.Uq = 0;
            MC.Foc.SinVal = 0; // 强制电角度0°
            MC.Foc.CosVal = 1;

            if (MC.Foc.Ud >= MC.Identify.VoltageSet[1]) // 校准用的电压与参数识别时一致
            {
                MC.Foc.Ud = 0;
                MC.Encoder.CalibFlag = 0;
                MC.Encoder.CalibOffset = MC.Encoder.EncoderVal; // 记录编码器零点与电角度零点的偏移量

                MC.Motor.RunMode = POS_SPEED_CURRENT_LOOP; // 完成转子校准，进入控制模式

                /* 初始化位置累加器为0 */
                MC.Position.ElectricalPosSum = 0;
                MC.Position.ElectricalPosLast = MC.Encoder.ElectricalVal;
            }
        }

        park_inv_transform(&MC.Foc);
    }
    break;
    case CURRENT_OPEN_LOOP: // 电流开环
    {
        park_inv_transform(&MC.Foc); // 给定Uq值电机转动
    }
    break;
    case CURRENT_CLOSE_LOOP: // 电流闭环
    {
        MC.IqPid.Ref = MC.Sample.AdcBuff[1] * 0.002f; // 使用波轮电位器给电机目标电流Iq_ref电机转动
        MC.IdPid.Ref = 0;

        /* 电流环 */
        MC.Foc.Iu = MC.Sample.IuReal;
        MC.Foc.Iv = MC.Sample.IvReal;
        clarke_transform(&MC.Foc);                                                               // Iu,Iv → Iα,Iβ
        park_transform(&MC.Foc);                                                                 // Iα,Iβ → Id,Iq
        MC.Foc.IdLPF = MC.Foc.Id * MC.Foc.IdLPFFactor + MC.Foc.IdLPF * (1 - MC.Foc.IdLPFFactor); // Id低通滤波
        MC.Foc.IqLPF = MC.Foc.Iq * MC.Foc.IqLPFFactor + MC.Foc.IqLPF * (1 - MC.Foc.IqLPFFactor); // Iq低通滤波
        MC.IqPid.Fbk = MC.Foc.IqLPF;
        MC.IdPid.Fbk = MC.Foc.IdLPF;
        pid_calculate(&MC.IqPid); // 输出Uq
        pid_calculate(&MC.IdPid); // 输出Ud
        MC.Foc.Uq = MC.IqPid.Out;
        MC.Foc.Ud = MC.IdPid.Out;
        park_inv_transform(&MC.Foc); // Ud,Uq → Uα,Uβ
    }
    break;
    case SPEED_CURRENT_LOOP: // 速度闭环+电流闭环
    {
        MC.Speed.SpeedCalculateCnt++;
        MC.Speed.MechanicalSpeedSet = (MC.Sample.AdcBuff[1] > 50 ? MC.Sample.AdcBuff[1] : 0); // 使用波轮电位器给电机目标转速

        /* 速度环 */
        if (MC.Speed.SpeedCalculateCnt >= SPEED_DIVISION_FACTOR)
        {
            MC.Speed.SpeedCalculateCnt = 0;
            MC.Speed.ElectricalPosThis = MC.Encoder.ElectricalVal; // 获取当前电角度
            speed_calculate(&MC.Speed);                            // 根据当前电角度和上次电角度计算电角速度
            MC.Speed.ElectricalSpeedLPF = MC.Speed.ElectricalSpeedRaw * MC.Speed.ElectricalSpeedLPFFactor + MC.Speed.ElectricalSpeedLPF * (1 - MC.Speed.ElectricalSpeedLPFFactor);
            MC.Speed.MechanicalSpeed = MC.Speed.ElectricalSpeedLPF / MC.Encoder.PolePairs; // 转换为机械速度

            if (MC.Speed.MechanicalSpeedSet != MC.Speed.MechanicalSpeedSetLast) // 给定了新的目标速度
            {
                MC.TAccDec.StartSpeed = MC.Speed.MechanicalSpeedSetLast * MC.Encoder.PolePairs; // 设置初速度
                MC.TAccDec.EndSpeed = MC.Speed.MechanicalSpeedSet * MC.Encoder.PolePairs;       // 设置末速度

                tshape_acc_dec(&MC.TAccDec); // T形加减速计算

                if (MC.TAccDec.FinishFlag == 1) // 执行完加减速
                {
                    MC.Speed.MechanicalSpeedSetLast = MC.Speed.MechanicalSpeedSet; // 更新上次目标速度
                    MC.TAccDec.FinishFlag = 0;
                }
            }

            MC.SpdPid.Ref = MC.TAccDec.SpeedOut;         // 获得目标值
            MC.SpdPid.Fbk = MC.Speed.ElectricalSpeedLPF; // 反馈速度值

            if (MC.SpdPid.Fbk > -2000 && MC.SpdPid.Fbk < 2000)
            {
                MC.SpdPid.Kp = MC.SpdPid.KpMax; // 低速区，提高增益，增强响应
            }
            else
            {
                MC.SpdPid.Kp = MC.SpdPid.KpMin; // 高速区，降低增益，防止超调
            }

            pid_calculate(&MC.SpdPid);    // 速度闭环PID计算
            MC.IqPid.Ref = MC.SpdPid.Out; // 速度环输出作为电流环输入
        }

        /* 电流环 */
        MC.Foc.Iu = MC.Sample.IuReal;
        MC.Foc.Iv = MC.Sample.IvReal;
        clarke_transform(&MC.Foc);
        park_transform(&MC.Foc);
        MC.Foc.IdLPF = MC.Foc.Id * MC.Foc.IdLPFFactor + MC.Foc.IdLPF * (1 - MC.Foc.IdLPFFactor);
        MC.Foc.IqLPF = MC.Foc.Iq * MC.Foc.IqLPFFactor + MC.Foc.IqLPF * (1 - MC.Foc.IqLPFFactor);
        MC.IqPid.Fbk = MC.Foc.IqLPF;
        MC.IdPid.Fbk = MC.Foc.IdLPF;
        pid_calculate(&MC.IqPid);
        pid_calculate(&MC.IdPid);
        MC.Foc.Uq = MC.IqPid.Out;
        MC.Foc.Ud = MC.IdPid.Out;
        park_inv_transform(&MC.Foc);
    }
    break;
    case POS_SPEED_CURRENT_LOOP: // 位置闭环+速度闭环+电流闭环
    {
        MC.Position.PosCalculateCnt++;
        MC.Speed.SpeedCalculateCnt++;
        MC.Position.MechanicalPosSet = -MC.Sample.AdcBuff[1]; // 使用波轮电位器给电机目标位置

        /* 位置环 */
        if (MC.Position.PosCalculateCnt >= POS_DIVISION_FACTOR)
        {
            MC.Position.PosCalculateCnt = 0;
            MC.Position.ElectricalPosThis = MC.Encoder.ElectricalVal; // 获取当前位置
            position_calculate(&MC.Position);                         // 计算总位置
            MC.PosPid.Fbk = MC.Position.ElectricalPosSum;             // 反馈实际位置
            MC.PosPid.Ref = MC.Position.MechanicalPosSet * POLEPAIRS; // 给定目标位置
            MC.Position.MechanicalPosRaw = MC.Position.ElectricalPosSum / POLEPAIRS;
            pid_calculate(&MC.PosPid); // 位置闭环PID计算
        }

        /* 速度环 */
        if (MC.Speed.SpeedCalculateCnt >= SPEED_DIVISION_FACTOR)
        {
            MC.Speed.SpeedCalculateCnt = 0;
            MC.Speed.ElectricalPosThis = MC.Encoder.ElectricalVal;
            speed_calculate(&MC.Speed); // 计算速度
            MC.Speed.ElectricalSpeedLPF = MC.Speed.ElectricalSpeedRaw * MC.Speed.ElectricalSpeedLPFFactor + MC.Speed.ElectricalSpeedLPF * (1 - MC.Speed.ElectricalSpeedLPFFactor);
            MC.Speed.MechanicalSpeed = MC.Speed.ElectricalSpeedLPF / POLEPAIRS;
            MC.SpdPid.Ref = MC.PosPid.Out;               // 给定速度值
            MC.SpdPid.Fbk = MC.Speed.ElectricalSpeedLPF; // 反馈速度值

            if (MC.SpdPid.Fbk > -2000 && MC.SpdPid.Fbk < 2000)
            {
                MC.SpdPid.Kp = MC.SpdPid.KpMax;
            }
            else
            {
                MC.SpdPid.Kp = MC.SpdPid.KpMin;
            }

            pid_calculate(&MC.SpdPid); // 速度闭环PID计算
            MC.IqPid.Ref = MC.SpdPid.Out;
        }

        /* 电流环 */
        MC.Foc.Iu = MC.Sample.IuReal;
        MC.Foc.Iv = MC.Sample.IvReal;
        clarke_transform(&MC.Foc);
        park_transform(&MC.Foc);
        MC.Foc.IdLPF = MC.Foc.Id * MC.Foc.IdLPFFactor + MC.Foc.IdLPF * (1 - MC.Foc.IdLPFFactor);
        MC.Foc.IqLPF = MC.Foc.Iq * MC.Foc.IqLPFFactor + MC.Foc.IqLPF * (1 - MC.Foc.IqLPFFactor);
        MC.IqPid.Fbk = MC.Foc.IqLPF;
        MC.IdPid.Fbk = MC.Foc.IdLPF;
        pid_calculate(&MC.IqPid);
        pid_calculate(&MC.IdPid);
        MC.Foc.Uq = MC.IqPid.Out;
        MC.Foc.Ud = MC.IdPid.Out;
        park_inv_transform(&MC.Foc);
    }
    break;
    }

    /* SVPWM调制 */
    MC.Foc.Ubus = MC.Sample.BusReal; // 更新母线电压
    svpwm_calculate(&MC.Foc);        // 生成三相PWM占空比
}

/**
 * @brief 无感控制
 */
void sensorless_ctrl(void)
{
}
