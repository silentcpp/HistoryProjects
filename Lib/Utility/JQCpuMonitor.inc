#ifndef JQLIBRARY_INCLUDE_JQCPUMONITOR_INC_
#define JQLIBRARY_INCLUDE_JQCPUMONITOR_INC_

// .h include
#include "JQCPUMonitor.h"

inline QString Utility::JQCPUMonitor::cpuUsagePercentageDisplayString()
{
    return QString( "%1%" ).arg( static_cast< int >( cpuUsagePercentage() * 100 ) );
}

inline QString Utility::JQCPUMonitor::cpuUsagePercentageIn5SecondDisplayString()
{
    return QString( "%1%" ).arg( static_cast< int >( cpuUsagePercentageIn5Second() * 100 ) );
}

inline QString Utility::JQCPUMonitor::cpuUsagePercentageIn30SecondDisplayString()
{
    return QString( "%1%" ).arg( static_cast< int >( cpuUsagePercentageIn30Second() * 100 ) );
}

inline QString Utility::JQCPUMonitor::cpuUsagePercentageIn5MinuteDisplayString()
{
    return QString( "%1%" ).arg( static_cast< int >( cpuUsagePercentageIn5Minute() * 100 ) );
}

inline QString Utility::JQCPUMonitor::cpuUsagePercentageInTimeDisplayString(const qint64 &msecs)
{
    return QString( "%1%" ).arg( static_cast< int >( cpuUsagePercentageInTime( msecs ) * 100 ) );
}

inline qreal Utility::JQCPUMonitor::cpuUsagePercentageIn5Second()
{
    return cpuUsagePercentageInTime( 5 * 1000 );
}

inline qreal Utility::JQCPUMonitor::cpuUsagePercentageIn30Second()
{
    return cpuUsagePercentageInTime( 30 * 1000 );
}

inline qreal Utility::JQCPUMonitor::cpuUsagePercentageIn5Minute()
{
    return cpuUsagePercentageInTime( 5 * 50 * 1000 );
}

#endif//JQLIBRARY_INCLUDE_JQCPUMONITOR_INC_
