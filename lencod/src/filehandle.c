
/*!
 **************************************************************************************
 * \file
 *    filehandle.c
 * \brief
 *    Start and terminate sequences
 * \author
 *    Main contributors (see contributors.h for copyright, address and affiliation details)
 *      - Thomas Stockhammer            <stockhammer@ei.tum.de>
 *      - Detlev Marpe                  <marpe@hhi.de>
 ***************************************************************************************
 */

#include "contributors.h"

#include "global.h"
#include "enc_statistics.h"

#include "rtp.h"
#include "annexb.h"
#include "parset.h"
#include "mbuffer.h"


/*!
 ************************************************************************
 * \brief
 *    Error handling procedure. Print error message to stderr and exit
 *    with supplied code.
 * \param text
 *    Error message
 * \param code
 *    Exit code
 ************************************************************************
 */
void error(char *text, int code)
{
  fprintf(stderr, "%s\n", text);
  flush_dpb();
  exit(code);
}

/*!
 ************************************************************************
 * \brief
 *     This function generates and writes the PPS
 *
 ************************************************************************
 */
int write_PPS(int len, int PPS_id)
{
  NALU_t *nalu;
  nalu = NULL;
  nalu = GeneratePic_parameter_set_NALU (PPS_id);
  len += WriteNALU (nalu);
  FreeNALU (nalu);

  return len;
}

/*!
 ************************************************************************
 * \brief
 *    This function opens the output files and generates the
 *    appropriate sequence header
 ************************************************************************
 */
int start_sequence(void)
{
  int i,len=0, total_pps = (params->GenerateMultiplePPS) ? 3 : 1;
  NALU_t *nalu;


  switch(params->of_mode)
  {
    case PAR_OF_ANNEXB:
      OpenAnnexbFile (params->outfile);
      WriteNALU = WriteAnnexbNALU;
      break;
    case PAR_OF_RTP:
      OpenRTPFile (params->outfile);
      WriteNALU = WriteRTPNALU;
      break;
    default:
      snprintf(errortext, ET_SIZE, "Output File Mode %d not supported", params->of_mode);
      error(errortext,1);
      return 1;
  }

  // Access Unit Delimiter NALU
  if ( params->SendAUD )
  {
    len += Write_AUD_NALU();
  }

  //! As a sequence header, here we write both sequence and picture
  //! parameter sets.  As soon as IDR is implemented, this should go to the
  //! IDR part, as both parsets have to be transmitted as part of an IDR.
  //! An alternative may be to consider this function the IDR start function.

  nalu = NULL;
  nalu = GenerateSeq_parameter_set_NALU ();
  len += WriteNALU (nalu);
  FreeNALU (nalu);

  //! Lets write now the Picture Parameter sets. Output will be equal to the total number of bits spend here.
  for (i=0;i<total_pps;i++)
  {
     len = write_PPS(len, i);
  }

  if (params->GenerateSEIMessage)
  {
    nalu = NULL;
    nalu = GenerateSEImessage_NALU();
    len += WriteNALU (nalu);
    FreeNALU (nalu);
  }

  stats->bit_ctr_parametersets_n = len;
  return 0;
}

/*!
 ************************************************************************
 * \brief
 *    This function opens the output files and generates the
 *    appropriate sequence header
 ************************************************************************
 */
int rewrite_paramsets(void)
{
  int i,len=0, total_pps = (params->GenerateMultiplePPS) ? 3 : 1;
  NALU_t *nalu;

  // Access Unit Delimiter NALU
  if ( params->SendAUD )
  {
    len += Write_AUD_NALU();
  }

  //! As a sequence header, here we write both sequence and picture
  //! parameter sets.  As soon as IDR is implemented, this should go to the
  //! IDR part, as both parsets have to be transmitted as part of an IDR.
  //! An alternative may be to consider this function the IDR start function.

  nalu = NULL;
  nalu = GenerateSeq_parameter_set_NALU ();
  len += WriteNALU (nalu);
  FreeNALU (nalu);

  //! Lets write now the Picture Parameter sets. Output will be equal to the total number of bits spend here.
  for (i=0;i<total_pps;i++)
  {
     len = write_PPS(len, i);
  }

  if (params->GenerateSEIMessage)
  {
    nalu = NULL;
    nalu = GenerateSEImessage_NALU();
    len += WriteNALU (nalu);
    FreeNALU (nalu);
  }

  stats->bit_ctr_parametersets_n = len;
  return 0;
}

/*!
 ************************************************************************
 * \brief
 *     This function terminates the sequence and closes the
 *     output files
 ************************************************************************
 */
int terminate_sequence(void)
{
//  Bitstream *currStream;

  // Mainly flushing of everything
  // Add termination symbol, etc.

  switch(params->of_mode)
  {
    case PAR_OF_ANNEXB:
      CloseAnnexbFile();
      break;
    case PAR_OF_RTP:
      CloseRTPFile();
      return 0;
    default:
      snprintf(errortext, ET_SIZE, "Output File Mode %d not supported", params->of_mode);
      error(errortext,1);
      return 1;
  }
  return 1;   // make lint happy
}

