/**
 *  @addtogroup  Hareware Middle Layer
 *  @brief       Hardware Middle Layer, to access data from BSP and STM32 HAL Library
 *
 *  @{
 *      @file       HWDataAccess.c
 *      @brief      middleware, for UI and APP Layer to get the hardware data
 *      @details    you can enable or disable in .h file.
 * 					加这个文件就是为了方便UI移植, 比如你要把工程移植到PC仿真,
 *   				直接把MidFunc中的文件和UI文件都复制过去,
 * 					然后直接把.h文件中的HW_USE_HARDWARE变成0就行了.
 */

#include "../Inc/HWDataAccess.h"


/**************************************************************************/
/*!
    @brief  to get the real time clock from the hardware

    @param  nowdatetime to storge the data&time

	@return None
*/
/**************************************************************************/
void HW_RTC_Get_TimeDate(HW_DateTimeTypeDef * nowdatetime)
{
	#if HW_USE_RTC
		if (nowdatetime != NULL)
		{
            RTC_DateTypeDef nowdate;
            RTC_TimeTypeDef nowtime;
			HAL_RTC_GetTime(&hrtc, &nowtime, RTC_FORMAT_BIN);
			HAL_RTC_GetDate(&hrtc, &nowdate, RTC_FORMAT_BIN);
            nowdatetime->Year = nowdate.Year;
            nowdatetime->Month = nowdate.Month;
            nowdatetime->Date = nowdate.Date;
			nowdatetime->WeekDay = weekday_calculate(nowdatetime->Year, nowdatetime->Month, nowdatetime->Date, 20);
            nowdatetime->Hours = nowtime.Hours;
            nowdatetime->Minutes = nowtime.Minutes;
            nowdatetime->Seconds = nowtime.Seconds;
		}
	#else
		nowdatetime->Year = 24;
		nowdatetime->Month = 6;
		nowdatetime->Date = 23;
		nowdatetime->WeekDay = 7;
		nowdatetime->Hours = 11;
		nowdatetime->Minutes = 59;
		nowdatetime->Seconds = 55;
	#endif
}


/**************************************************************************/
/*!
    @brief  to set the RTC Date to hardware

    @param  nowdatetime to storge the data&time

	@return None
*/
/**************************************************************************/
void HW_RTC_Set_Date(uint8_t year, uint8_t month, uint8_t date)
{
	#if HW_USE_RTC
		RTC_SetDate(year, month, date);
	#endif
}

/**************************************************************************/
/*!
    @brief  to set the RTC Date to hardware

    @param  nowdatetime to storge the data&time

	@return None
*/
/**************************************************************************/
void HW_RTC_Set_Time(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
	#if HW_USE_RTC
		RTC_SetTime(hours, minutes, seconds);
	#endif
}

/**************************************************************************/
/*!
    @brief  to calculate the weekday

    @param  nowdatetime to storge the data&time

	@return None
*/
/**************************************************************************/
uint8_t HW_weekday_calculate(uint8_t setyear, uint8_t setmonth, uint8_t setday, uint8_t century)
{
	int w;
	if (setmonth == 1 || setmonth == 2)
	{setyear--, setmonth += 12;}
	w = setyear + setyear / 4 + century / 4  + 26*(setmonth + 1)/10 + setday - 1 - 2 * century;
	while(w<0)
		w+=7;
	w%=7;
	w=(w==0)?7:w;
	return w;
}


/**************************************************************************/
/*!
    @brief  check the MPU Wrist wake up is enabled or not

    @param	NULL

	@return true if the Wrist wake up is enabled
*/
/**************************************************************************/
uint8_t HW_MPU_Wrist_is_Enabled(void)
{
	#if HW_USE_IMU
		if(user_MPU_Wrist_EN)
		{
			return true;
		}
	#endif
	return false;
}


/**************************************************************************/
/*!
    @brief  set the MPU Wrist wake up to enabled

    @param	NULL

	@return NULL
*/
/**************************************************************************/
void HW_MPU_Wrist_Enable(void)
{
	#if HW_USE_IMU
		user_MPU_Wrist_EN = 1;
	#endif
}


/**************************************************************************/
/*!
    @brief  set the MPU Wrist wake up to disabled

    @param	NULL

	@return NULL
*/
/**************************************************************************/
void HW_MPU_Wrist_Disable(void)
{
	#if HW_USE_IMU
		user_MPU_Wrist_EN = 0;
	#endif
}

/**************************************************************************/
/*!
    @brief  enable BLE

    @param	NULL

	@return NULL
*/
/**************************************************************************/
void HW_BLE_Enable(void)
{
	#if HW_USE_BLE
		KT6328_Enable();
	#endif
}


/**************************************************************************/
/*!
    @brief  disable BLE

    @param	NULL

	@return NULL
*/
/**************************************************************************/
void HW_BLE_Disable(void)
{
	#if HW_USE_BLE
		KT6328_Disable();
	#endif
}


/**************************************************************************/
/*!
    @brief shutdown the power

    @param	NULL

	@return NULL
*/
/**************************************************************************/
void HW_Power_Shutdown(void)
{
	#if HW_USE_BAT
		Power_DisEnable();
	#endif
}


/**************************************************************************/
/*!
    @brief shutdown the power

    @param	NULL

	@return NULL
*/
/**************************************************************************/
void HW_LCD_Set_Light(uint8_t dc)
{
	#if HW_USE_LCD
		LCD_Set_Light(dc);
	#endif
}

