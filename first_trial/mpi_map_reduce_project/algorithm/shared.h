//
// Created by enaki on 12.01.2021.
//

#ifndef MPI_MAP_REDUCE_PROJECT_SHARED_H
#define MPI_MAP_REDUCE_PROJECT_SHARED_H

#include <ctime>
#include <unordered_map>
#include <list>
#include <chrono>
#include <sstream>
#include <random>

typedef std::pair<std::string, unsigned long long> PAIR_STRING_COUNT;

//#define DEBUG
#define MASTER 7
#define SIZE 8
#define WORKER_SIZE 7

#define MAP_DIRECT_INDEX_PHASE 100

#define PREPARE_FOR_REDUCE_DIRECT_INDEX_PHASE 101
#define REDUCE_DIRECT_INDEX_PHASE 102

#define PREPARE_FOR_MAP_INDIRECT_INDEX_PHASE 103
#define MAP_INDIRECT_INDEX_PHASE 104

#define PREPARE_FOR_REDUCE_INDIRECT_INDEX_PHASE 105
#define REDUCE_INDIRECT_INDEX_PHASE 106

#define START_WORK 200
#define FINISHED_WORK 201
#define FINISHED_PREPARING 202

#define TEMP_FOLDER "temp"
#define TEMP_FOLDER_DIRECT_IDX_PHASE "temp/direct"
#define TEMP_FOLDER_DIRECT_IDX_PHASE_MAPPERS "temp/direct/mappers"
#define TEMP_FOLDER_DIRECT_IDX_PHASE_REDUCERS "temp/direct/reducers"
#define TEMP_FOLDER_INDIRECT_IDX_PHASE "temp/indirect"
#define TEMP_FOLDER_INDIRECT_IDX_PHASE_MAPPERS "temp/indirect/mappers"
#define TEMP_FOLDER_INDIRECT_IDX_PHASE_REDUCERS "temp/indirect/reducers"
#define TEMP_FOLDER_INDIRECT_IDX_PHASE_WORDS "temp/indirect/words"
#define OUTPUT_FOLDER "output"

bool is_preparing_phase(int tag){
    if (tag == PREPARE_FOR_REDUCE_DIRECT_INDEX_PHASE || tag == PREPARE_FOR_MAP_INDIRECT_INDEX_PHASE || tag == PREPARE_FOR_REDUCE_INDIRECT_INDEX_PHASE){
        return true;
    }
    return false;
}

const char* get_tag_name(int tag){
    switch (tag) {
        case MAP_DIRECT_INDEX_PHASE:
            return "MAP_DIRECT_INDEX_PHASE";
        case PREPARE_FOR_REDUCE_DIRECT_INDEX_PHASE:
            return "PREPARE_FOR_REDUCE_DIRECT_INDEX_PHASE";
        case REDUCE_DIRECT_INDEX_PHASE:
            return "REDUCE_DIRECT_INDEX_PHASE";
        case PREPARE_FOR_MAP_INDIRECT_INDEX_PHASE:
            return "PREPARE_FOR_MAP_INDIRECT_INDEX_PHASE";
        case MAP_INDIRECT_INDEX_PHASE:
            return "MAP_INDIRECT_INDEX_PHASE";
        case PREPARE_FOR_REDUCE_INDIRECT_INDEX_PHASE:
            return "PREPARE_FOR_REDUCE_INDIRECT_INDEX_PHASE";
        case REDUCE_INDIRECT_INDEX_PHASE:
            return "REDUCE_INDIRECT_INDEX_PHASE";
        case START_WORK:
            return "START_WORK";
        case FINISHED_WORK:
            return "FINISHED_WORK";
        case FINISHED_PREPARING:
            return "FINISHED_PREPARING";
        default:
            return "UNDEFINED";
    }
}

bool all_workers_are_done(const bool *are_worker_active){
    for (int i = 0; i < WORKER_SIZE; ++i){
        if (are_worker_active[i]){
            return false;
        }
    }
    return true;
}

int get_idle_worker(const bool *are_worker_active){
    for (int i = 0; i < WORKER_SIZE; ++i){
        if (!are_worker_active[i]){
            return i;
        }
    }
    return -1;
}

void log(int rank, int target, int tag, const char* message=""){
    if (rank == MASTER){
        printf("[ MASTER ] - Received message <%s> with tag <%s> from %d\n", message, get_tag_name(tag), target);
    } else {
        if (tag == REDUCE_INDIRECT_INDEX_PHASE){
            return;
        }
        if (tag == PREPARE_FOR_MAP_INDIRECT_INDEX_PHASE || tag == PREPARE_FOR_REDUCE_DIRECT_INDEX_PHASE || tag == PREPARE_FOR_REDUCE_INDIRECT_INDEX_PHASE){
            printf("[ WORKER %d ] - Received message <> with tag <%s> from %d\n", rank, get_tag_name(tag), target);

        } else {
            printf("[ WORKER %d ] - Received message <%s> with tag <%s> from %d\n", rank, message, get_tag_name(tag), target);
        }
    }
}

#endif //MPI_MAP_REDUCE_PROJECT_SHARED_H
