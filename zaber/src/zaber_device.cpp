/*
 * @Author: Lukasz
 * @Date:   04-10-2018
 * @Last Modified by:   Lukasz
 * @Last Modified time: 10-10-2018
 */

#include "zaber/zaber_device.h"
#include "zaber/zaber_control.h"
namespace zaber
{

/**
 * \date       09-Oct-2018
 * \brief      Gets the range.
 *
 * \param[in]  id    Product ID
 *
 * \return     The range.
 *
 * \details
 * \warning    Please check that your device is supported.
 */
double get_range(const DeviceID id)
{
  switch (id)
  {
  case DeviceID::X_LHM025A:
  case DeviceID::X_LHM025A_E03:
  case DeviceID::X_LHM025A_S:
  case DeviceID::X_LHM025A_SE03:
  case DeviceID::X_LRM025A:
  case DeviceID::X_LRM025A_DE51:
  case DeviceID::X_LRM025A_E03:
  case DeviceID::X_LRM025B:
  case DeviceID::X_LRM025B_DE51:
  case DeviceID::X_LRM025B_E03:
  case DeviceID::X_LSM025A:
  case DeviceID::X_LSM025A_E03:
  case DeviceID::X_LSM025A_S:
  case DeviceID::X_LSM025A_SE03:
  case DeviceID::X_LSM025A_SV1:
  case DeviceID::X_LSM025A_SV2:
  case DeviceID::X_LSM025B:
  case DeviceID::X_LSM025B_E03:
  case DeviceID::X_LSM025B_S:
  case DeviceID::X_LSM025B_SE03:
  case DeviceID::X_LSM025B_SV1:
  case DeviceID::X_LSM025B_SV2:
  case DeviceID::LHM025A_E03T3:
  case DeviceID::LHM025A_T3:
  case DeviceID::LRM025A_E03T3:
  case DeviceID::LRM025A_T3:
  case DeviceID::LRM025B_E03T3:
  case DeviceID::LRM025B_T3:
  case DeviceID::LSM025A_E03T4:
  case DeviceID::LSM025A_M02T4:
  case DeviceID::LSM025A_T4_rev_1:
  case DeviceID::LSM025A_T4_rev_2:
  case DeviceID::LSM025A_V1T4:
  case DeviceID::LSM025A_V2T4:
  case DeviceID::LSM025B_E03T4:
  case DeviceID::LSM025B_T4_rev_1:
  case DeviceID::LSM025B_T4_rev_2:
  case DeviceID::LSM025B_V1T4:
  case DeviceID::LSM025B_V2T4: return 25e-3;
  case DeviceID::X_LHM050A:
  case DeviceID::X_LHM050A_E03:
  case DeviceID::X_LHM050A_S:
  case DeviceID::X_LHM050A_SE03:
  case DeviceID::X_LRM050A:
  case DeviceID::X_LRM050A_DE51:
  case DeviceID::X_LRM050A_E03:
  case DeviceID::X_LRM050B:
  case DeviceID::X_LRM050B_DE51:
  case DeviceID::X_LRM050B_E03:
  case DeviceID::X_LSM050A:
  case DeviceID::X_LSM050A_E03:
  case DeviceID::X_LSM050A_S:
  case DeviceID::X_LSM050A_SE03:
  case DeviceID::X_LSM050A_SV1:
  case DeviceID::X_LSM050A_SV2:
  case DeviceID::X_LSM050B:
  case DeviceID::X_LSM050B_E03:
  case DeviceID::X_LSM050B_S:
  case DeviceID::X_LSM050B_SE03:
  case DeviceID::X_LSM050B_SV1:
  case DeviceID::X_LSM050B_SV2:
  case DeviceID::LHM050A_E03T3:
  case DeviceID::LHM050A_T3:
  case DeviceID::LRM050A_E03T3:
  case DeviceID::LRM050A_T3:
  case DeviceID::LRM050B_E03T3:
  case DeviceID::LRM050B_T3:
  case DeviceID::LSM050A_E03T4:
  case DeviceID::LSM050A_T4_rev_1:
  case DeviceID::LSM050A_T4_rev_2:
  case DeviceID::LSM050A_V1T4:
  case DeviceID::LSM050A_V2T4:
  case DeviceID::LSM050B_E03T4:
  case DeviceID::LSM050B_T4_rev_1:
  case DeviceID::LSM050B_T4_rev_2:
  case DeviceID::LSM050B_V1T4:
  case DeviceID::LSM050B_V2T4: return 50e-3;
  case DeviceID::A_LSQ075A:
  case DeviceID::A_LSQ075A_E01:
  case DeviceID::A_LSQ075B:
  case DeviceID::A_LSQ075B_E01:
  case DeviceID::A_LSQ075D:
  case DeviceID::A_LSQ075D_E01:
  case DeviceID::X_LRQ075AL_DE51:
  case DeviceID::X_LRQ075AL_DE51C:
  case DeviceID::X_LRQ075AL_E01:
  case DeviceID::X_LRQ075AL_E01C:
  case DeviceID::X_LRQ075AL_SV1:
  case DeviceID::X_LRQ075AL_SV2:
  case DeviceID::X_LRQ075AP_DE51:
  case DeviceID::X_LRQ075AP_DE51C:
  case DeviceID::X_LRQ075AP_E01:
  case DeviceID::X_LRQ075AP_E01C:
  case DeviceID::X_LRQ075BL_DE51:
  case DeviceID::X_LRQ075BL_DE51C:
  case DeviceID::X_LRQ075BL_E01:
  case DeviceID::X_LRQ075BL_E01C:
  case DeviceID::X_LRQ075BL_SV1:
  case DeviceID::X_LRQ075BL_SV2:
  case DeviceID::X_LRQ075BP_DE51:
  case DeviceID::X_LRQ075BP_DE51C:
  case DeviceID::X_LRQ075BP_E01:
  case DeviceID::X_LRQ075BP_E01C:
  case DeviceID::X_LRQ075DL_E01:
  case DeviceID::X_LRQ075DL_E01C:
  case DeviceID::X_LRQ075DP_E01:
  case DeviceID::X_LRQ075DP_E01C:
  case DeviceID::X_LRQ075HL_DE51:
  case DeviceID::X_LRQ075HL_DE51C:
  case DeviceID::X_LRQ075HL_E01:
  case DeviceID::X_LRQ075HL_E01C:
  case DeviceID::X_LRQ075HP_DE51:
  case DeviceID::X_LRQ075HP_DE51C:
  case DeviceID::X_LRQ075HP_E01:
  case DeviceID::X_LRQ075HP_E01C:
  case DeviceID::X_LSM075A:
  case DeviceID::X_LSM075A_E03:
  case DeviceID::X_LSM075A_S:
  case DeviceID::X_LSM075A_SE03:
  case DeviceID::X_LSM075A_SV1:
  case DeviceID::X_LSM075A_SV2:
  case DeviceID::X_LSM075B:
  case DeviceID::X_LSM075B_E03:
  case DeviceID::X_LSM075B_S:
  case DeviceID::X_LSM075B_SE03:
  case DeviceID::X_LSM075B_SV1:
  case DeviceID::X_LSM075B_SV2:
  case DeviceID::X_LSQ075A:
  case DeviceID::X_LSQ075A_E01:
  case DeviceID::X_LSQ075B:
  case DeviceID::X_LSQ075B_E01:
  case DeviceID::X_LSQ075D:
  case DeviceID::X_LSQ075D_E01:
  case DeviceID::G_LSQ075A_T4:
  case DeviceID::G_LSQ075B_T4:
  case DeviceID::G_LSQ075D_T4:
  case DeviceID::LRQ075AL_DE51CT3:
  case DeviceID::LRQ075AL_DE51T3:
  case DeviceID::LRQ075AL_E01CT3:
  case DeviceID::LRQ075AL_E01T3:
  case DeviceID::LRQ075AL_V1T3:
  case DeviceID::LRQ075AL_V2T3:
  case DeviceID::LRQ075AP_DE51CT3:
  case DeviceID::LRQ075AP_DE51T3:
  case DeviceID::LRQ075AP_E01CT3:
  case DeviceID::LRQ075AP_E01T3:
  case DeviceID::LRQ075BL_DE51CT3:
  case DeviceID::LRQ075BL_DE51T3:
  case DeviceID::LRQ075BL_E01CT3:
  case DeviceID::LRQ075BL_E01T3:
  case DeviceID::LRQ075BL_V1T3:
  case DeviceID::LRQ075BL_V2T3:
  case DeviceID::LRQ075BP_DE51CT3:
  case DeviceID::LRQ075BP_DE51T3:
  case DeviceID::LRQ075BP_E01CT3:
  case DeviceID::LRQ075BP_E01T3:
  case DeviceID::LRQ075DL_E01CT3:
  case DeviceID::LRQ075DL_E01T3:
  case DeviceID::LRQ075DL_V1T3:
  case DeviceID::LRQ075DL_V2T3:
  case DeviceID::LRQ075DP_E01CT3:
  case DeviceID::LRQ075DP_E01T3:
  case DeviceID::LRQ075HL_DE51CT3:
  case DeviceID::LRQ075HL_DE51T3:
  case DeviceID::LRQ075HL_E01CT3:
  case DeviceID::LRQ075HL_E01T3:
  case DeviceID::LRQ075HP_DE51CT3:
  case DeviceID::LRQ075HP_DE51T3:
  case DeviceID::LRQ075HP_E01CT3:
  case DeviceID::LRQ075HP_E01T3:
  case DeviceID::LSM075A_E03T4:
  case DeviceID::LSM075A_T4_rev_1:
  case DeviceID::LSM075A_T4_rev_2:
  case DeviceID::LSM075A_V1T4:
  case DeviceID::LSM075A_V2T4:
  case DeviceID::LSM075B_E03T4:
  case DeviceID::LSM075B_T4_rev_1:
  case DeviceID::LSM075B_T4_rev_2:
  case DeviceID::LSM075B_V1T4:
  case DeviceID::LSM075B_V2T4:
  case DeviceID::LSQ075A_E01T3:
  case DeviceID::LSQ075A_T3:
  case DeviceID::LSQ075B_E01T3:
  case DeviceID::LSQ075B_T3:
  case DeviceID::LSQ075D_E01T3:
  case DeviceID::LSQ075D_T3: return 75e-3;
  case DeviceID::X_LHM100A:
  case DeviceID::X_LHM100A_E03:
  case DeviceID::X_LHM100A_S:
  case DeviceID::X_LHM100A_SE03:
  case DeviceID::X_LRM100A:
  case DeviceID::X_LRM100A_DE51:
  case DeviceID::X_LRM100A_E03:
  case DeviceID::X_LRM100B:
  case DeviceID::X_LRM100B_DE51:
  case DeviceID::X_LRM100B_E03:
  case DeviceID::X_LRT0100AL_C:
  case DeviceID::X_LRT0100AL_DE51C:
  case DeviceID::X_LRT0100AL_E08C:
  case DeviceID::X_LRT0100AP_C:
  case DeviceID::X_LRT0100AP_DE51C:
  case DeviceID::X_LRT0100AP_E08C:
  case DeviceID::X_LRT0100BL_C:
  case DeviceID::X_LRT0100BL_DE51C:
  case DeviceID::X_LRT0100BL_E08C:
  case DeviceID::X_LRT0100BP_C:
  case DeviceID::X_LRT0100BP_DE51C:
  case DeviceID::X_LRT0100BP_E08C:
  case DeviceID::X_LRT0100DL_C:
  case DeviceID::X_LRT0100DL_DE51C:
  case DeviceID::X_LRT0100DL_E08C:
  case DeviceID::X_LRT0100DP_C:
  case DeviceID::X_LRT0100DP_DE51C:
  case DeviceID::X_LRT0100DP_E08C:
  case DeviceID::X_LRT0100HL_C:
  case DeviceID::X_LRT0100HL_DE51C:
  case DeviceID::X_LRT0100HL_E08C:
  case DeviceID::X_LRT0100HP_C:
  case DeviceID::X_LRT0100HP_DE51C:
  case DeviceID::X_LRT0100HP_E08C:
  case DeviceID::X_LSM100A:
  case DeviceID::X_LSM100A_E03:
  case DeviceID::X_LSM100A_S:
  case DeviceID::X_LSM100A_SE03:
  case DeviceID::X_LSM100A_SV1:
  case DeviceID::X_LSM100A_SV2:
  case DeviceID::X_LSM100B:
  case DeviceID::X_LSM100B_E03:
  case DeviceID::X_LSM100B_S:
  case DeviceID::X_LSM100B_SE03:
  case DeviceID::X_LSM100B_SV1:
  case DeviceID::X_LSM100B_SV2:
  case DeviceID::LHM100A_E03T3:
  case DeviceID::LHM100A_T3:
  case DeviceID::LRM100A_E03T3:
  case DeviceID::LRM100A_T3:
  case DeviceID::LRM100B_E03T3:
  case DeviceID::LRM100B_T3:
  case DeviceID::LRT0100AL_CT3:
  case DeviceID::LRT0100AL_DE51CT3:
  case DeviceID::LRT0100AL_E08CT3:
  case DeviceID::LRT0100AP_CT3:
  case DeviceID::LRT0100AP_DE51CT3:
  case DeviceID::LRT0100AP_E08CT3:
  case DeviceID::LRT0100BL_CT3:
  case DeviceID::LRT0100BL_DE51CT3:
  case DeviceID::LRT0100BL_E08CT3:
  case DeviceID::LRT0100BP_CT3:
  case DeviceID::LRT0100BP_DE51CT3:
  case DeviceID::LRT0100BP_E08CT3:
  case DeviceID::LRT0100DL_CT3:
  case DeviceID::LRT0100DL_DE51CT3:
  case DeviceID::LRT0100DL_E08CT3:
  case DeviceID::LRT0100DP_CT3:
  case DeviceID::LRT0100DP_DE51CT3:
  case DeviceID::LRT0100DP_E08CT3:
  case DeviceID::LRT0100HL_CT3:
  case DeviceID::LRT0100HL_DE51CT3:
  case DeviceID::LRT0100HL_E08CT3:
  case DeviceID::LRT0100HP_CT3:
  case DeviceID::LRT0100HP_DE51CT3:
  case DeviceID::LRT0100HP_E08CT3:
  case DeviceID::LSM100A_E03T4:
  case DeviceID::LSM100A_T4_rev_1:
  case DeviceID::LSM100A_T4_rev_2:
  case DeviceID::LSM100A_V1T4:
  case DeviceID::LSM100A_V2T4:
  case DeviceID::LSM100B_E03T4:
  case DeviceID::LSM100B_T4_rev_1:
  case DeviceID::LSM100B_T4_rev_2:
  case DeviceID::LSM100B_V1T4:
  case DeviceID::LSM100B_V2T4: return 100e-3;
  case DeviceID::A_BAR200BLC:
  case DeviceID::A_BAR200BLC_E01:
  case DeviceID::A_BAR200BPC:
  case DeviceID::A_BAR200BPC_E01:
  case DeviceID::A_LAR200ALC:
  case DeviceID::A_LAR200ALC_E01:
  case DeviceID::A_LAR200APC:
  case DeviceID::A_LAR200APC_E01:
  case DeviceID::X_LHM200A:
  case DeviceID::X_LHM200A_E03:
  case DeviceID::X_LHM200A_S:
  case DeviceID::X_LHM200A_SE03:
  case DeviceID::X_LRM200A:
  case DeviceID::X_LRM200A_DE51:
  case DeviceID::X_LRM200A_E03:
  case DeviceID::X_LRM200B:
  case DeviceID::X_LRM200B_DE51:
  case DeviceID::X_LRM200B_E03:
  case DeviceID::X_LSM200A:
  case DeviceID::X_LSM200A_E03:
  case DeviceID::X_LSM200A_S:
  case DeviceID::X_LSM200A_SE03:
  case DeviceID::X_LSM200A_SV1:
  case DeviceID::X_LSM200A_SV2:
  case DeviceID::X_LSM200B:
  case DeviceID::X_LSM200B_E03:
  case DeviceID::X_LSM200B_S:
  case DeviceID::X_LSM200B_SE03:
  case DeviceID::X_LSM200B_SV1:
  case DeviceID::X_LSM200B_SV2:
  case DeviceID::BAR200BLC_E01T3:
  case DeviceID::BAR200BLC_T3:
  case DeviceID::BAR200BPC_E01T3:
  case DeviceID::BAR200BPC_T3:
  case DeviceID::LAR200ALC_E01T3:
  case DeviceID::LAR200ALC_T3:
  case DeviceID::LAR200APC_E01T3:
  case DeviceID::LAR200APC_T3:
  case DeviceID::LHM200A_E03T3:
  case DeviceID::LHM200A_T3:
  case DeviceID::LRM200A_E03T3:
  case DeviceID::LRM200A_T3:
  case DeviceID::LRM200B_E03T3:
  case DeviceID::LRM200B_T3:
  case DeviceID::LSM200A_E03T4:
  case DeviceID::LSM200A_T4_rev_1:
  case DeviceID::LSM200A_T4_rev_2:
  case DeviceID::LSM200A_V1T4:
  case DeviceID::LSM200A_V2T4:
  case DeviceID::LSM200B_E03T4:
  case DeviceID::LSM200B_T4_rev_1:
  case DeviceID::LSM200B_T4_rev_2:
  case DeviceID::LSM200B_V1T4:
  case DeviceID::LSM200B_V2T4: return 200e-3;
  case DeviceID::A_BAR300BLC:
  case DeviceID::A_BAR300BLC_E01:
  case DeviceID::A_BAR300BPC:
  case DeviceID::A_BAR300BPC_E01:
  case DeviceID::A_LAR300ALC:
  case DeviceID::A_LAR300ALC_E01:
  case DeviceID::A_LAR300APC:
  case DeviceID::A_LAR300APC_E01:
  case DeviceID::A_LSQ300A:
  case DeviceID::A_LSQ300A_E01:
  case DeviceID::A_LSQ300B:
  case DeviceID::A_LSQ300B_E01:
  case DeviceID::A_LSQ300D:
  case DeviceID::A_LSQ300D_E01:
  case DeviceID::X_LRQ300AL_DE51:
  case DeviceID::X_LRQ300AL_DE51C:
  case DeviceID::X_LRQ300AL_E01:
  case DeviceID::X_LRQ300AL_E01C:
  case DeviceID::X_LRQ300AL_SV1:
  case DeviceID::X_LRQ300AL_SV2:
  case DeviceID::X_LRQ300AP_DE51:
  case DeviceID::X_LRQ300AP_DE51C:
  case DeviceID::X_LRQ300AP_E01:
  case DeviceID::X_LRQ300AP_E01C:
  case DeviceID::X_LRQ300BL_DE51:
  case DeviceID::X_LRQ300BL_DE51C:
  case DeviceID::X_LRQ300BL_E01:
  case DeviceID::X_LRQ300BL_E01C:
  case DeviceID::X_LRQ300BL_SV1:
  case DeviceID::X_LRQ300BL_SV2:
  case DeviceID::X_LRQ300BP_DE51:
  case DeviceID::X_LRQ300BP_DE51C:
  case DeviceID::X_LRQ300BP_E01:
  case DeviceID::X_LRQ300BP_E01C:
  case DeviceID::X_LRQ300DL_E01:
  case DeviceID::X_LRQ300DL_E01C:
  case DeviceID::X_LRQ300DP_E01:
  case DeviceID::X_LRQ300DP_E01C:
  case DeviceID::X_LRQ300HL_DE51:
  case DeviceID::X_LRQ300HL_DE51C:
  case DeviceID::X_LRQ300HL_E01:
  case DeviceID::X_LRQ300HL_E01C:
  case DeviceID::X_LRQ300HP_DE51:
  case DeviceID::X_LRQ300HP_DE51C:
  case DeviceID::X_LRQ300HP_E01:
  case DeviceID::X_LRQ300HP_E01C:
  case DeviceID::X_LSQ300A:
  case DeviceID::X_LSQ300A_E01:
  case DeviceID::X_LSQ300B:
  case DeviceID::X_LSQ300B_E01:
  case DeviceID::X_LSQ300D:
  case DeviceID::X_LSQ300D_E01:
  case DeviceID::BAR300BLC_E01T3:
  case DeviceID::BAR300BLC_T3:
  case DeviceID::BAR300BPC_E01T3:
  case DeviceID::BAR300BPC_T3:
  case DeviceID::G_LSQ300A_T4:
  case DeviceID::G_LSQ300B_T4:
  case DeviceID::G_LSQ300D_T4:
  case DeviceID::LAR300ALC_E01T3:
  case DeviceID::LAR300ALC_T3:
  case DeviceID::LAR300APC_E01T3:
  case DeviceID::LAR300APC_T3:
  case DeviceID::LRQ300AL_DE51CT3:
  case DeviceID::LRQ300AL_DE51T3:
  case DeviceID::LRQ300AL_E01CT3:
  case DeviceID::LRQ300AL_E01T3:
  case DeviceID::LRQ300AL_V1T3:
  case DeviceID::LRQ300AL_V2T3:
  case DeviceID::LRQ300AP_DE51CT3:
  case DeviceID::LRQ300AP_DE51T3:
  case DeviceID::LRQ300AP_E01CT3:
  case DeviceID::LRQ300AP_E01T3:
  case DeviceID::LRQ300BL_DE51CT3:
  case DeviceID::LRQ300BL_DE51T3:
  case DeviceID::LRQ300BL_E01CT3:
  case DeviceID::LRQ300BL_E01T3:
  case DeviceID::LRQ300BL_V1T3:
  case DeviceID::LRQ300BL_V2T3:
  case DeviceID::LRQ300BP_DE51CT3:
  case DeviceID::LRQ300BP_DE51T3:
  case DeviceID::LRQ300BP_E01CT3:
  case DeviceID::LRQ300BP_E01T3:
  case DeviceID::LRQ300DL_E01CT3:
  case DeviceID::LRQ300DL_E01T3:
  case DeviceID::LRQ300DL_V1T3:
  case DeviceID::LRQ300DL_V2T3:
  case DeviceID::LRQ300DP_E01CT3:
  case DeviceID::LRQ300DP_E01T3:
  case DeviceID::LRQ300HL_DE51CT3:
  case DeviceID::LRQ300HL_DE51T3:
  case DeviceID::LRQ300HL_E01CT3:
  case DeviceID::LRQ300HL_E01T3:
  case DeviceID::LRQ300HP_DE51CT3:
  case DeviceID::LRQ300HP_DE51T3:
  case DeviceID::LRQ300HP_E01CT3:
  case DeviceID::LRQ300HP_E01T3:
  case DeviceID::LSQ300A_E01T3:
  case DeviceID::LSQ300A_T3:
  case DeviceID::LSQ300B_E01T3:
  case DeviceID::LSQ300B_T3:
  case DeviceID::LSQ300D_E01T3:
  case DeviceID::LSQ300D_T3: return 300e-3;
  case DeviceID::A_LST0500A:
  case DeviceID::A_LST0500A_C:
  case DeviceID::A_LST0500A_E01:
  case DeviceID::A_LST0500A_E01C:
  case DeviceID::A_LST0500B:
  case DeviceID::A_LST0500B_C:
  case DeviceID::A_LST0500B_E01:
  case DeviceID::A_LST0500B_E01C:
  case DeviceID::A_LST0500D:
  case DeviceID::A_LST0500D_C:
  case DeviceID::A_LST0500D_E01:
  case DeviceID::A_LST0500D_E01C:
  case DeviceID::X_LRT0500AL_C:
  case DeviceID::X_LRT0500AL_DE51C:
  case DeviceID::X_LRT0500AL_E08C:
  case DeviceID::X_LRT0500AP_C:
  case DeviceID::X_LRT0500AP_DE51C:
  case DeviceID::X_LRT0500AP_E08C:
  case DeviceID::X_LRT0500BL_C:
  case DeviceID::X_LRT0500BL_DE51C:
  case DeviceID::X_LRT0500BL_E08C:
  case DeviceID::X_LRT0500BP_C:
  case DeviceID::X_LRT0500BP_DE51C:
  case DeviceID::X_LRT0500BP_E08C:
  case DeviceID::X_LRT0500DL_C:
  case DeviceID::X_LRT0500DL_DE51C:
  case DeviceID::X_LRT0500DL_E08C:
  case DeviceID::X_LRT0500DP_C:
  case DeviceID::X_LRT0500DP_DE51C:
  case DeviceID::X_LRT0500DP_E08C:
  case DeviceID::X_LRT0500HL_C:
  case DeviceID::X_LRT0500HL_DE51C:
  case DeviceID::X_LRT0500HL_E08C:
  case DeviceID::X_LRT0500HP_C:
  case DeviceID::X_LRT0500HP_DE51C:
  case DeviceID::X_LRT0500HP_E08C:
  case DeviceID::LRT0500AL_CT3:
  case DeviceID::LRT0500AL_DE51CT3:
  case DeviceID::LRT0500AL_E08CT3:
  case DeviceID::LRT0500AP_CT3:
  case DeviceID::LRT0500AP_DE51CT3:
  case DeviceID::LRT0500AP_E08CT3:
  case DeviceID::LRT0500BL_CT3:
  case DeviceID::LRT0500BL_DE51CT3:
  case DeviceID::LRT0500BL_E08CT3:
  case DeviceID::LRT0500BP_CT3:
  case DeviceID::LRT0500BP_DE51CT3:
  case DeviceID::LRT0500BP_E08CT3:
  case DeviceID::LRT0500DL_CT3:
  case DeviceID::LRT0500DL_DE51CT3:
  case DeviceID::LRT0500DL_E08CT3:
  case DeviceID::LRT0500DP_CT3:
  case DeviceID::LRT0500DP_DE51CT3:
  case DeviceID::LRT0500DP_E08CT3:
  case DeviceID::LRT0500HL_CT3:
  case DeviceID::LRT0500HL_DE51CT3:
  case DeviceID::LRT0500HL_E08CT3:
  case DeviceID::LRT0500HP_CT3:
  case DeviceID::LRT0500HP_DE51CT3:
  case DeviceID::LRT0500HP_E08CT3:
  case DeviceID::LST0500A_E01T3:
  case DeviceID::LST0500A_T3:
  case DeviceID::LST0500B_E01T3:
  case DeviceID::LST0500B_T3:
  case DeviceID::LST0500D_E01T3:
  case DeviceID::LST0500D_T3: return 500e-3;

  default: return 0e0;
  }
}

std::shared_ptr<spdlog::logger> Device::m_log = spdlog::stdout_color_mt("device");

Device::Device(Controller* const ctrl, const Address address, const DeviceID id) : m_ctrl(ctrl), m_address(address), m_id(id)
{

  m_log->trace("{} id = {}, at {}", __FUNCTION__, static_cast<uint>(m_id), m_address);

  if (ctrl == nullptr)
  {
    m_log->error("Controller cannot be null!");
    throw std::invalid_argument("Controller cannot be null!");
  }
}

Device::~Device() {}

/**
 * \date       10-Oct-2018
 * \brief      Determines if busy.
 *
 * \return     True if busy, False otherwise.
 *
 * \details    Sends empty command to get the device status.
 */
bool Device::is_busy(void) const { return ((command(Command::None))->status == Status::BUSY); }

/**
 * \date       10-Oct-2018
 * \brief      Simply poll the device until IDLE.
 */
void Device::wait_until_idle(void) const
{
  while (is_busy())
    ;
}

/**
 * \author     lokraszewski
 * \date       03-Oct-2018
 * \brief      Decelerates an axis and brings it to a halt.
 *
 */
void Device::stop(void) const { (void)command(Command::Stop); }

/**
\author     lokraszewski
\date       02-Oct-2018
\brief      Instantly stops motorized movement.

\details    Firmware Versions 6.06+

The axis ignores the deceleration setting, immediately stops driving the motion,
and holds the current position. Example Usage :
\code
/1 1 estop↵
@01 1 OK BUSY-- 0
\endcode

\warning    The axis remains powered and will respond to future movement
            commands.

\warning    Excessive use of this command may result in potential damage to
            the product and reduced lifespan. Use sparingly if axis is under
            heavy load.
*/
void Device::emergency_stop(void) const { (void)command(Command::EmergencyStop); }

/**
 \author     lokraszewski
 \date       02-Oct-2018
 \brief      Moves the axis to the home position.

 \details    The axis is moved towards the home position(closest to the motor
             generally) at the lesser of the limit.approach .maxspeed and
             maxspeed settings.Once the home position is reached, the current
             position is reset to the limit.home.preset.Additionally,
             limit.home.triggered is set to 1, and the No Reference
             Position(WR) warning flag is cleared.This command is equivalent
             to tools gotolimit home neg 2 0. Example Usage :
 \code
 / home↵
 01 0 OK BUSY WR 0
 \endcode
 \warning    Upon power up or setting changes, this command should be issued
             to obtain a reference position.Otherwise, motion commands may
             respond with a rejection reply or behave unexpectedly.
*/
void Device::home(void) const { (void)command(Command::Home); }

/**
 * \date       10-Oct-2018
 * \brief      Resets the device, as it would appear after power up
 *
 * \details    This command sets the Setting Update Pending (NU) notification
 *             flag and replies. Once all communication channels have been quiet
 *             for 500 milliseconds, the device resets and clears the Setting
 *             Update Pending (NU) flag.
 */
void Device::reset(void) const { (void)command(Command::SystemReset); }

/**
 * \date       10-Oct-2018
 * \brief      Restores common device settings to their default values.
 *
 * \details    This command resets common settings to their default for the
 *             device and peripheral. Communications settings are not modified.
 */
void Device::restore_defaults(void) const { (void)command(Command::SystemRestore); }

/**
 * \date       10-Oct-2018
 * \brief      Stores a number of positions for axes for ease of movement.
 *
 * \param[in]  number  The number
 * \param[in]  pos     The position
 *
 * \details    number is the stored position number to be set or retrieved. The
 *             valid range is 1 - 16. position is a valid axis position to move
 *             to and must be in the range of limit.min to limit.max. The
 *             position defaults to 0 if not set.
 */
void Device::store_position(const uint8_t number, const size_t pos) const { (void)command<>(Command::StorePosition, number, pos); }

/**
 * \date       10-Oct-2018
 * \brief      Stores a number of positions for axes for ease of movement.
 *
 * \param[in]  number  The number
 *
 * \details    number is the stored position number to be set or retrieved. The
 *             valid range is 1 - 16. current specifies that the specified
 *             stored position number be set to the current position, pos. If
 *             none of the optional arguments are provided, the current value of
 *             the stored position number will be returned.
 */
void Device::store_position(const uint8_t number) const { (void)command<>(Command::StorePosition, "current"); }

/**
 * \author     lokraszewski
 *
 * \date       03-Oct-2018
 * \brief      stored moves the axis to a previously stored position.
 *
 * \param[in]  number  Number specifies the stored position number, from 1 - 16.
 *
 * \details    Number specifies the stored position number, from 1 - 16. Refer
 *             to the tools storepos command for more information.
 */
void Device::move_stored(const uint8_t number) const { (void)command<>(Command::MoveStored, number); }

/**
 * \author     lokraszewski
 *
 * \date       03-Oct-2018
 * \brief      abs moves to the absolute position of value.
 *
 * \param[in]  value  Value must be in the range [ limit.min, limit.max ].
 *
 */
void Device::move_absolute(const int value) { (void)command<>(Command::MoveAbsolute, value); }

/**
 * \author     lokraszewski
 *
 * \date       03-Oct-2018
 * \brief      rel moves the axis by value microsteps, relative to the current
 *             position.
 *
 * \param[in]  value  Value must be in the range [ limit.min - pos, limit.max -
 *                    pos ].
 *
 */
void Device::move_relative(int value) { (void)command<>(Command::MoveRelative, value); }

/**
 * \author     lokraszewski
 * \date       03-Oct-2018
 * \brief      vel moves the axis at the velocity specified by value until a
 *             limit is reached.
 *
 * \param[in]  value  Value must be in the range [ -resolution * 16384,
 *                    resolution * 16384 ].
 *
 */
void Device::move_velocity(int value) { (void)command<>(Command::MoveVelocity, value); }
/**
 * \author     lokraszewski
 * \date       03-Oct-2018
 * \brief      min moves the axis to the minimum position, as specified by
 *             limit.min.
 *
 */
void Device::move_min(void) { (void)command(Command::MoveMin); }
/**
 * \author     lokraszewski
 * \date       03-Oct-2018
 * \brief      max moves the axis to the maximum position, as specified by
 *             limit.max.
 *
 */
void Device::move_max(void) { (void)command(Command::MoveMax); }

/**
 * \author     lokraszewski
 * \date       03-Oct-2018
 * \brief      index moves the axis to an index position. For a provided
 *             number, this command directs the axis to move to the absolute
 *             position (number - 1) * motion.index.dist.
 *
 * \param[in]  index  Note that only positive values of number are accepted.
 *
 * \details    For rotary devices with a non-zero limit.cycle.dist, the
 *             command will be accepted if the targeted position is greater or
 *             equal to 0 and less than limit.cycle.dist. The device will move
 *             either clockwise or counter-clockwise, depending on which
 *             direction yields the shortest distance to the target position.
 *             If you want all index positions to be equally spaced around the
 *             circle, set motion.index.dist to a factor of limit.cycle.dist.
 *             For linear devices, or rotary devices where limit.cycle.dist is
 *             zero, the command will be accepted if the targeted position is
 *             within the valid travel of the device, i.e. in the range [
 *             limit.min, limit.max ].
 */
void Device::move_index(unsigned int index) { (void)command<>(Command::MoveIndex, index); }

DeviceID Device::get_device_id(void) const { return m_id; }
int      Device::get_position(void) const { return get_setting<int>("pos"); }
int      Device::get_max(void) const { return get_setting<int>("limit.max"); }
int      Device::get_min(void) const { return get_setting<int>("limit.min"); }
int      Device::get_home_position(void) const { return get_setting<int>("limit.home.pos"); }
uint8_t  Device::get_resolution(void) const { return get_setting<uint8_t>("resolution"); }
int      Device::get_max_velocity(void) const
{
  const auto res = get_resolution();
  // The velocity range is given as  [ -resolution * 16384, resolution * 16384
  // ]. See https://www.zaber.com/wiki/Manuals/ASCII_Protocol_Manual#move Here
  // we just return the positive limit and assume the negative is the inverse
  return 16384 * res;
}

std::shared_ptr<Reply> Device::command(const Command cmd) const { return m_ctrl->command(m_address, cmd); }

} // namespace zaber
