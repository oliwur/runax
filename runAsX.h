//
// Created by oliwu on 09/09/2019.
//

#ifndef RUNAX_RUNASX_H
#define RUNAX_RUNASX_H

#include <stdbool.h>

void startProcessAsUser(wchar_t *user,
                        wchar_t *password,
                        wchar_t *domain,
                        bool netonly,
                        wchar_t *executable,
                        wchar_t *args);

#endif //RUNAX_RUNASX_H
