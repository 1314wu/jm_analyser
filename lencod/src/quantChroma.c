
/*!
 *************************************************************************************
 * \file quantChroma.c
 *
 * \brief
 *    Quantization initialization function for Chroma blocks
 *
 * \author
 *    Main contributors (see contributors.h for copyright, address and affiliation details)
 *    - Alexis Michael Tourapis                  <alexismt@ieee.org>
 *
 *************************************************************************************
 */

#include "contributors.h"

#include "global.h"
#include "quant4x4.h"
#include "quantChroma.h"

/*!
************************************************************************
* \brief
*    Quantization initialization function
*
************************************************************************
*/
void init_quant_Chroma(InputParameters *params, ImageParameters *img, Slice *currSlice)
{
  if (params->UseRDOQuant == 1 && params->RDOQ_CR == 1)
  {
    quant_ac4x4cr = quant_ac4x4_trellis;
    if (params->RDOQ_DC_CR)
    {
      if (img->yuv_format == YUV422)
        quant_dc_cr = quant_dc4x2_trellis;
      else
        quant_dc_cr = quant_dc2x2_trellis;
    }
    else
    {
      if (img->yuv_format == YUV422)
        quant_dc_cr   = quant_dc4x2_normal;
      else
        quant_dc_cr   = quant_dc2x2_normal;
    }
    if (currSlice->symbol_mode == CABAC)
      rdoq_dc_cr = rdoq_dc_cr_CABAC;
    else
      rdoq_dc_cr = rdoq_dc_cr_CAVLC;
  }
  else if (params->UseRDOQuant == 1 || (!img->AdaptiveRounding))
  {
    quant_ac4x4cr = quant_ac4x4_normal;
    if (img->yuv_format == YUV422)
      quant_dc_cr   = quant_dc4x2_normal;
    else
      quant_dc_cr   = quant_dc2x2_normal;
  }
  else
  {
    quant_ac4x4cr = quant_ac4x4_around;
    if (img->yuv_format == YUV422)
      quant_dc_cr   = quant_dc4x2_around;
    else
      quant_dc_cr   = quant_dc2x2_around;
  }
}


