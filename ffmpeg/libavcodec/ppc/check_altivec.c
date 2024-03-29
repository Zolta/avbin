/*
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */


/**
 * @file check_altivec.c
 * Checks for AltiVec presence.
 */

#ifdef __APPLE__
#undef _POSIX_C_SOURCE
#include <sys/sysctl.h>
#elif __OpenBSD__
#include <sys/param.h>
#include <sys/sysctl.h>
#include <machine/cpu.h>
#elif __AMIGAOS4__
#include <exec/exec.h>
#include <interfaces/exec.h>
#include <proto/exec.h>
#endif /* __APPLE__ */

/**
 * This function MAY rely on signal() or fork() in order to make sure AltiVec
 * is present.
 */

int has_altivec(void)
{
#ifdef __AMIGAOS4__
    ULONG result = 0;
    extern struct ExecIFace *IExec;

    IExec->GetCPUInfoTags(GCIT_VectorUnit, &result, TAG_DONE);
    if (result == VECTORTYPE_ALTIVEC) return 1;
    return 0;
#elif defined(__APPLE__) || defined(__OpenBSD__)
#ifdef __OpenBSD__
    int sels[2] = {CTL_MACHDEP, CPU_ALTIVEC};
#else
    int sels[2] = {CTL_HW, HW_VECTORUNIT};
#endif
    int has_vu = 0;
    size_t len = sizeof(has_vu);
    int err;

    err = sysctl(sels, 2, &has_vu, &len, NULL, 0);

    if (err == 0) return has_vu != 0;
    return 0;
#elif defined(RUNTIME_CPUDETECT)
    int proc_ver;
    // Support of mfspr PVR emulation added in Linux 2.6.17.
    __asm__ volatile("mfspr %0, 287" : "=r" (proc_ver));
    proc_ver >>= 16;
    if (proc_ver  & 0x8000 ||
        proc_ver == 0x000c ||
        proc_ver == 0x0039 || proc_ver == 0x003c ||
        proc_ver == 0x0044 || proc_ver == 0x0045 ||
        proc_ver == 0x0070)
        return 1;
    return 0;
#else
    // Since we were compiled for AltiVec, just assume we have it
    // until someone comes up with a proper way (not involving signal hacks).
    return 1;
#endif /* __AMIGAOS4__ */
}

