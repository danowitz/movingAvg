// Arduino Moving Average Library
// https://github.com/JChristensen/movingAvg
// Copyright (C) 2018 by Jack Christensen and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html

#include <movingAvg.h>

// initialize - allocate the interval array
void movingAvg::begin()
{
    m_readings = new int[m_interval];
}

float movingAvg::reading(float newReading){
    int val = (int)round(newReading*1000);
    
    reading(val);
    return getAvgf();
}

// add a new reading and return the new moving average
int movingAvg::reading(int newReading)
{
    // add each new data point to the sum until the m_readings array is filled
    if (m_nbrReadings < m_interval)
    {
        ++m_nbrReadings;
        m_sum = m_sum + newReading;
    }
    // once the array is filled, subtract the oldest data point and add the new one
    else
    {
        m_sum = m_sum - m_readings[m_next] + newReading;
    }

    m_readings[m_next] = newReading;
    if (++m_next >= m_interval) m_next = 0;
    return (m_sum + m_nbrReadings / 2) / m_nbrReadings;
}

// just return the current moving average
int movingAvg::getAvg()
{
    return (m_sum + m_nbrReadings / 2) / m_nbrReadings;
}

// just return the current moving average
int movingAvg::getAvg()
{
    if(m_nbrReadings > 0) {
        return (m_sum + m_nbrReadings / 2) / m_nbrReadings;
    } else {
        return 0;
    }
}

float movingAvg::getAvgf() {
    return (float)(getAvg()/1000.0);
}

// start the moving average over again
void movingAvg::reset()
{
    m_nbrReadings = 0;
    m_sum = 0;
    m_next = 0;
}
