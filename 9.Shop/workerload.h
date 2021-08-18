#pragma once
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "struct.h"

void * workerload(void *);
