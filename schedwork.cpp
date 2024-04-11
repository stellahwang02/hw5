#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool schedHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts, 
    DailySchedule sched,
    size_t day,
    int worker,
    std::vector<size_t>& workerShifts
) {
    if (day == avail.size()) { // base case: all days scheduled
      return true;
    }
    if (worker == workerShifts.size()) { // no more workers
      return false;
    }

    // worker cannot work today
    if (!avail[day][worker] || workerShifts[worker] >= maxShifts) {
      return schedHelper(avail, dailyNeed, maxShifts, sched, day, worker+1, workerShifts);
    }

    // if worker is avail. and doesn't exceed max shifts
    // there are two options here, we can schedule the worker, or we can not schedule the worker
    // schedule the worker for the curr day
    sched[day].push_back(worker);
    // update worker shifts 
    workerShifts[worker]++;

    // move on to the next day if daily need is filled, otherwise move on to the next worker
    size_t nextDay;
    int nextWorker;
    if (dailyNeed == sched[day].size()) {
      nextDay = day+1;
      nextWorker = 0;
    } else {
      nextDay = day;
      nextWorker = worker+1;
    }

    // next day 
    if (schedHelper(avail, dailyNeed, maxShifts, sched, nextDay, nextWorker, workerShifts)) {
        return true; // valid sched found 
    }

    // backtrack-- remove worker from curr day's sched
    sched[day].pop_back();
    // restore worker shifts
    workerShifts[worker]--;
    
    // don't schedule this worker for today
    return schedHelper(avail, dailyNeed, maxShifts, sched, day, worker+1, workerShifts);
}


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }

    // if availbility matrix is empty
    if(avail.empty()) {
        return false;
    }
    
    sched.clear();
    // Add your code below

    sched.resize(avail.size());
    std::vector<size_t> workerShifts(avail[0].size(), 0);
    return schedHelper(avail, dailyNeed, maxShifts, sched, 0, 0, workerShifts);

}

