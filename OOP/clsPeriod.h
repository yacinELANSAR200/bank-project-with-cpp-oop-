#pragma once
#include "clsDate.h"

class clsPeriod
{
public:

    clsDate StartDate;
    clsDate EndDate;

    clsPeriod(clsDate StartDate, clsDate DateTo)
    {
        this->StartDate = StartDate;
        this->EndDate = DateTo;
    }

    static bool IsOverlapPeriods(clsPeriod Period1, clsPeriod Period2)
    {
        if (
            clsDate::CompareDates(Period2.EndDate, Period1.StartDate) == clsDate::enDateCompare::Before
            ||
            clsDate::CompareDates(Period2.StartDate, Period1.EndDate) == clsDate::enDateCompare::After
            )
            return false;
        else
            return true;

    }


    bool IsOverLapWith(clsPeriod Period2)
    {
        return IsOverlapPeriods(*this, Period2);
    }

    void Print()
    {
        cout << "Period Start: ";
        StartDate.Print();


        cout << "Period End: ";
        EndDate.Print();


    }
    static short CalculatePeriodLengthInDays(clsPeriod Period, bool IncludeDays = false) {
        return clsDate::GetDifferenceInDays(Period.StartDate, Period.EndDate, IncludeDays);
    }
    short CalculatePeriodLengthInDays(bool IncludeDays = false) {
        return CalculatePeriodLengthInDays(*this, IncludeDays);
    }
    static bool IsDateWithinInPeriod(clsPeriod Period, clsDate Date) {
        return !(
            clsDate::CompareDates(Date, Period.StartDate) == clsDate::enDateCompare::Before
            ||
            clsDate::CompareDates(Date, Period.EndDate) == clsDate::enDateCompare::After
            );
    }
    bool IsDateWithinInPeriod(clsDate Date) {
        return IsDateWithinInPeriod(*this,Date);
    }
    static short CountOverlapDays(clsPeriod Period1, clsPeriod Period2) {


        short Period1Length = CalculatePeriodLengthInDays(Period1, true);
        short Period2Length = CalculatePeriodLengthInDays(Period2, true);
        short OverlapDays = 0;
        if (!IsOverlapPeriods(Period1, Period2))
        {
            return 0;
        }
        if (Period1Length < Period2Length)
        {
            while (clsDate::IsDate1BeforeDate2(Period1.StartDate, Period1.EndDate)) {
                if (IsDateWithinInPeriod(Period2, Period1.StartDate))
                {
                    OverlapDays++;
                }
                Period1.StartDate = clsDate::AddOneDay(Period1.StartDate);
            }
        }
        else {
            while (clsDate::IsDate1BeforeDate2(Period2.StartDate, Period2.EndDate)) {
                if (IsDateWithinInPeriod(Period1, Period2.StartDate))
                {
                    OverlapDays++;
                }
                Period2.StartDate = clsDate::AddOneDay(Period2.StartDate);
            }
        }
        return OverlapDays;
    }

    short CountOverlapDays(clsPeriod Period2) {
        return CountOverlapDays(*this, Period2);
    }
};
