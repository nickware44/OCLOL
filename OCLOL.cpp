/*		OCLOL.cpp								*/
/*		OpenCL Optimization Library				*/
/*		version 1.0								*/
/*		NickWare Group							*/

#include "stdafx.h"
#include "OCLOL.h"

OCLOL::OCLOL(cl::Device _D, cl::Kernel _K, const long _TV, const int _C)
{
	CU = _D.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>();
	MWGS = _D.getInfo<CL_DEVICE_MAX_WORK_GROUP_SIZE>();
	PWGSM = _K.getWorkGroupInfo<CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE>(_D);
	TaskVolume = _TV;
	Cores = _C;
	OGWGS = 0;
	OLWGS = 0;
}

void OCLOL::PerformOptimization()
{
	OGWGS = TaskVolume;
	OLWGS = Cores;

	int i = 1;

	while (OLWGS > MWGS || OLWGS % PWGSM || OLWGS % 8) {
		i++;
		OLWGS /= i;
	}
	
	if (!OLWGS) OLWGS = MWGS;

	if (!(TaskVolume%OLWGS)) return;

	OGWGS = OLWGS * (TaskVolume/OLWGS+1);
}

long OCLOL::GetGlobalWorkGroupSize()
{
	return OGWGS;
}

int OCLOL::GetLocalWorkGroupSize()
{
	return OLWGS;
}

OCLOL::~OCLOL()
{
}
