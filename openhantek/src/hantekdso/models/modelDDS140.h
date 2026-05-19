// SPDX-License-Identifier: GPL-2.0+

#pragma once

#include "hantekdso/dsomodel.h"

struct ModelDDS140 : public DSOModel {
    static const int ID = 0xDD14;
    ModelDDS140();
    void applyRequirements(HantekDsoControl *dsoControl) const override;
};
