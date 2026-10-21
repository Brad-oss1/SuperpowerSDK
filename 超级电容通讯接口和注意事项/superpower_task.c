#include "superpower_task.h"
#include "chassis_task.h"
#include "can_service.h"
#include "cmsis_os.h"
#include "referee.h"

extern chassis_move_t chassis_move;
extern robot_status_t robot_state;
extern power_heat_data_t power_heat_data;


void superpower_task(void const *pvParameters)
{
    osDelay(1);
    chassis_move.super_power.enableDCDC =1;
    chassis_move.super_power.systemRestart =0;
    chassis_move.super_power.useNewFeedbackMessage =1;
    chassis_move.super_power.enableActiveChargingLimit = 1;
    chassis_move.super_power.activeChargingLimitRatio = 229;//充满到90%需要多少自己改
    while(1)
    {
        //超电
        chassis_move.super_power.refereePowerLimit = robot_state.chassis_power_limit;
        chassis_move.super_power.refereeEnergyBuffer = power_heat_data.buffer_energy;
        // chassis_move.super_power.refereePowerLimit = 45;调试用
        // chassis_move.super_power.refereeEnergyBuffer = 50;
        CAN_SuperPower_Control(chassis_move.super_power);
        osDelay(1);
    }
}
