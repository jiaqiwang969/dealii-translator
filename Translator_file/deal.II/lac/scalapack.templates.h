//include/deal.II-translator/lac/scalapack.templates_0.txt
// ---------------------------------------------------------------------
//
// Copyright (C) 2017 - 2019 by the deal.II authors
//
// This file is part of the deal.II library.
//
// The deal.II library is free software; you can use it, redistribute
// it, and/or modify it under the terms of the GNU Lesser General
// Public License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// The full text of the license can be found in the file LICENSE.md at
// the top level directory of deal.II.
//
// ---------------------------------------------------------------------

#ifndef dealii_scalapack_templates_h
#define dealii_scalapack_templates_h


#include <deal.II/base/config.h>

#ifdef DEAL_II_WITH_SCALAPACK

#  include <deal.II/base/mpi.h>
#  include <deal.II/base/mpi.templates.h>

#  ifdef DEAL_II_HAVE_FP_EXCEPTIONS
#    include <cfenv>
#  endif

// useful examples:
// https://stackoverflow.com/questions/14147705/cholesky-decomposition-scalapack-error/14203864
// http://icl.cs.utk.edu/lapack-forum/viewtopic.php?t=139   // second post by
// Julien Langou
// https://andyspiros.wordpress.com/2011/07/08/an-example-of-blacs-with-c/
// http://qboxcode.org/trac/browser/qb/tags/rel1_63_4/src/Matrix.C
// https://gitlab.phys.ethz.ch/lwossnig/lecture/blob/a534f562dfb2ad5c564abe5c2356d5d956fb7218/examples/mpi/scalapack.cpp
// https://github.com/elemental/Elemental/blob/master/src/core/imports/scalapack.cpp
// https://scicomp.stackexchange.com/questions/7766/performance-optimization-or-tuning-possible-for-scalapack-gemm
//
// info:
// http://www.netlib.org/scalapack/slug/index.html       // User guide
// http://www.netlib.org/scalapack/slug/node135.html // How to Measure Errors

extern "C"
{
   /* Basic Linear Algebra Communication Subprograms (BLACS) declarations */ 
  // https://www.ibm.com/support/knowledgecenter/SSNR5K_4.2.0/com.ibm.cluster.pessl.v4r2.pssl100.doc/am6gr_dinitb.htm#dinitb

  /**
   * ?????????????????????????????????????????????????????????https://www.ibm.com/support/knowledgecenter/en/SSNR5K_4.2.0/com.ibm.cluster.pessl.v4r2.pssl100.doc/am6gr_dbpnf.htm???
   *
   */
  void
  Cblacs_pinfo(int *rank, int *nprocs);

  /**
   * ??????????????? @p what ??? @p icontxt. ?????? @p val
   * ????????????BLACS????????????????????????????????????????????????????????????
   * @p what =0??? @p icontxt
   * ?????????????????????BLACS_GRIDINIT???BLACS_GRIDMAP???
   * https://www.ibm.com/support/knowledgecenter/en/SSNR5K_4.2.0/com.ibm.cluster.pessl.v4r2.pssl100.doc/am6gr_dbget.htm
   *
   */
  void
  Cblacs_get(int icontxt, int what, int *val);

  /**
   * ?????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
   * ??????????????? @p context
   * ???BLACS???????????????????????????????????????????????????????????????????????????????????????BLACS????????????https://www.ibm.com/support/knowledgecenter/en/SSNR5K_4.2.0/com.ibm.cluster.pessl.v4r2.pssl100.doc/am6gr_dbint.htm
   *
   */
  void
  Cblacs_gridinit(int *       context,
                  const char *order,
                  int         grid_height,
                  int         grid_width);

  /**
   * ?????????????????????????????????https://www.ibm.com/support/knowledgecenter/en/SSNR5K_4.2.0/com.ibm.cluster.pessl.v4r2.pssl100.doc/am6gr_dbinfo.htm
   *
   */
  void
  Cblacs_gridinfo(int  context,
                  int *grid_height,
                  int *grid_width,
                  int *grid_row,
                  int *grid_col);

  /**
   * ??????????????????????????????BLACS???????????????????????????????????????
   *
   */
  void
  Cblacs_pcoord(int ictxt, int pnum, int *prow, int *pcol);

  /**
   * ????????????BLACS????????????
   *
   */
  void
  Cblacs_gridexit(int context);

  /**
   * ?????????????????????????????????????????????????????????????????????????????????????????????
   *
   */
  void
  Cblacs_barrier(int, const char *);

  /**
   * ????????????BLACS??????????????????????????????????????????
   *
   */
  void
  Cblacs_exit(int error_code);

  /**
   * ????????? @prsrc,  @p csrc
   * ????????????????????????????????????????????????????????????https://software.intel.com/en-us/mkl-developer-reference-c-gerv2d???
   *
   */
  void
  Cdgerv2d(int context, int M, int N, double *A, int lda, int rsrc, int csrc);
  void
  Csgerv2d(int context, int M, int N, float *A, int lda, int rsrc, int csrc);

  /**
   * ?????????????????????A??????????????????????????????????????? @p rdest
   * @p cdest
   * ???https://software.intel.com/en-us/mkl-developer-reference-c-2018-beta-gesd2d
   *
   */
  void
  Cdgesd2d(int context, int M, int N, double *A, int lda, int rdest, int cdest);
  void
  Csgesd2d(int context, int M, int N, float *A, int lda, int rdest, int cdest);

  /**
   * ???MPI??????BLACS?????????  @p comm.  ???
   *
   */
  int
  Csys2blacs_handle(MPI_Comm comm);

  /**
   * ??????????????????????????????????????????NUMber of Rows Or
   * Columns??????https://www.ibm.com/support/knowledgecenter/SSNR5K_4.2.0/com.ibm.cluster.pessl.v4r2.pssl100.doc/am6gr_dnumy.htm
   *
   */
  int
  numroc_(const int *n,
          const int *nb,
          const int *iproc,
          const int *isproc,
          const int *nprocs);

  /**
   * ??????N???N??????????????????????????????sub( A
   * )???Cholesky???????????????A(IA:IA+N-1,
   * JA:JA+N-1)???http://www.netlib.org/scalapack/explore-html/d5/d9e/pdpotrf_8f_source.html
   * https://www.ibm.com/support/knowledgecenter/SSNR5K_4.2.0/com.ibm.cluster.pessl.v4r2.pssl100.doc/am6gr_lpotrf.htm
   *
   */
  void
  pdpotrf_(const char *UPLO,
           const int * N,
           double *    A,
           const int * IA,
           const int * JA,
           const int * DESCA,
           int *       INFO);
  void
  pspotrf_(const char *UPLO,
           const int * N,
           float *     A,
           const int * IA,
           const int * JA,
           const int * DESCA,
           int *       INFO);

  /**
   * ???????????????????????????sub( A
   * )???LU????????????????????????????????????????????????http://www.netlib.org/scalapack/explore-html/df/dfe/pdgetrf_8f_source.html
   * https://www.ibm.com/support/knowledgecenter/en/SSNR5K_4.2.0/com.ibm.cluster.pessl.v4r2.pssl100.doc/am6gr_lgetrf.htm
   *
   */
  void
  pdgetrf_(const int *m,
           const int *n,
           double *   A,
           const int *IA,
           const int *JA,
           const int *DESCA,
           int *      ipiv,
           int *      INFO);
  void
  psgetrf_(const int *m,
           const int *n,
           float *    A,
           const int *IA,
           const int *JA,
           const int *DESCA,
           int *      ipiv,
           int *      INFO);

  /**
   * ??????PDPOTRF?????????Cholesky????????????sub( A ) =
   * U**T*U???L*L**T????????????????????????????????????sub( A ) =
   * A(IA:IA+N-1,JA:JA+N-1)?????????http://www.netlib.org/scalapack/explore-html/d2/d44/pdpotri_8f_source.html
   * https://www.ibm.com/support/knowledgecenter/SSNR5K_4.2.0/com.ibm.cluster.pessl.v4r2.pssl100.doc/am6gr_lpotri.htm
   * https://software.intel.com/en-us/mkl-developer-reference-c-p-potri
   *
   */
  void
  pdpotri_(const char *UPLO,
           const int * N,
           double *    A,
           const int * IA,
           const int * JA,
           const int * DESCA,
           int *       INFO);
  void
  pspotri_(const char *UPLO,
           const int * N,
           float *     A,
           const int * IA,
           const int * JA,
           const int * DESCA,
           int *       INFO);

  /**
   * PDGETRI??????PDGETRF?????????LU?????????????????????????????????????????????????????????U?????????????????????InvA?????????InvA*L=inv(U)?????????sub(
   * A )=A(IA:IA+N-1,JA:JA+N-1)???????????????InvA???
   * http://www.netlib.org/scalapack/explore-html/d3/df3/pdgetri_8f_source.html
   * https://www.ibm.com/support/knowledgecenter/SSNR5K_4.2.0/com.ibm.cluster.pessl.v4r2.pssl100.doc/am6gr_lgetri.htm
   *
   */
  void
  pdgetri_(const int *N,
           double *   A,
           const int *IA,
           const int *JA,
           const int *DESCA,
           const int *ipiv,
           double *   work,
           int *      lwork,
           int *      iwork,
           int *      liwork,
           int *      info);
  void
  psgetri_(const int *N,
           float *    A,
           const int *IA,
           const int *JA,
           const int *DESCA,
           const int *ipiv,
           float *    work,
           int *      lwork,
           int *      iwork,
           int *      liwork,
           int *      info);


  /**
   * PDTRTRI?????????????????????????????????sub( A ) =
   * A(IA:IA+N-1,JA:JA+N-1)?????????http://www.netlib.org/scalapack/explore-html/d9/dc0/pdtrtri_8f_source.html
   * https://www.ibm.com/support/knowledgecenter/SSNR5K_4.2.0/com.ibm.cluster.pessl.v4r2.pssl100.doc/am6gr_lpdtri.htm
   * https://software.intel.com/en-us/mkl-developer-reference-c-p-trtri
   *
   */
  void
  pdtrtri_(const char *UPLO,
           const char *DIAG,
           const int * N,
           double *    A,
           const int * IA,
           const int * JA,
           const int * DESCA,
           int *       INFO);
  void
  pstrtri_(const char *UPLO,
           const char *DIAG,
           const int * N,
           float *     A,
           const int * IA,
           const int * JA,
           const int * DESCA,
           int *       INFO);

  /**
   * ??????Cholesky??????????????????????????????????????????????????????????????????(l1-norm)???
   * https://www.ibm.com/support/knowledgecenter/SSNR5K_4.2.0/com.ibm.cluster.pessl.v4r2.pssl100.doc/am6gr_lpocon.htm#lpocon
   * http://www.netlib.org/scalapack/explore-html/d4/df7/pdpocon_8f.html
   * https://software.intel.com/en-us/mkl-developer-reference-fortran-pocon
   *
   */
  void
  pdpocon_(const char *  uplo,
           const int *   N,
           const double *A,
           const int *   IA,
           const int *   JA,
           const int *   DESCA,
           const double *ANORM,
           double *      RCOND,
           double *      WORK,
           const int *   LWORK,
           int *         IWORK,
           const int *   LIWORK,
           int *         INFO);
  void
  pspocon_(const char * uplo,
           const int *  N,
           const float *A,
           const int *  IA,
           const int *  JA,
           const int *  DESCA,
           const float *ANORM,
           float *      RCOND,
           float *      WORK,
           const int *  LWORK,
           int *        IWORK,
           const int *  LIWORK,
           int *        INFO);

  /**
   * ????????????????????????
   * http://www.netlib.org/scalapack/explore-html/dd/d12/pdlansy_8f_source.html
   * https://www.ibm.com/support/knowledgecenter/SSNR5K_4.2.0/com.ibm.cluster.pessl.v4r2.pssl100.doc/am6gr_pdlansy.htm#pdlansy
   *
   */
  double
  pdlansy_(const char *  norm,
           const char *  uplo,
           const int *   N,
           const double *A,
           const int *   IA,
           const int *   JA,
           const int *   DESCA,
           double *      work);
  float
  pslansy_(const char * norm,
           const char * uplo,
           const int *  N,
           const float *A,
           const int *  IA,
           const int *  JA,
           const int *  DESCA,
           float *      work);

  /**
   * ????????????????????? @p M ??? @p N. ?????????????????????LCM???
   * ?????????????????????????????????????????????GCD???????????????M*N=GCD*LCM????????????http://www.netlib.org/scalapack/explore-html/d0/d9b/ilcm_8f_source.html
   *
   */
  int
  ilcm_(const int *M, const int *N);

  /**
   * ???????????????????????????????????????http://www.netlib.org/scalapack/explore-html/df/d07/iceil_8f_source.html
   *
   */
  int
  iceil_(const int *i1, const int *i2);

  /**
   * ???8???????????????????????????????????????
   *
   */
  void
  descinit_(int *      desc,
            const int *m,
            const int *n,
            const int *mb,
            const int *nb,
            const int *irsrc,
            const int *icsrc,
            const int *ictxt,
            const int *lld,
            int *      info);

  /**
   * ????????? @p iproc. ??????????????????????????? @p indxloc
   * ?????????????????????????????????????????????  @param  indxloc
   * ???????????????????????????????????????    @param  nb
   * ?????????????????????????????????????????????????????????    @param
   * iproc ???????????????????????????????????????????????????  @param
   * isrcproc ??????????????????????????????/?????????????????????  @param
   * nprocs ??????????????????????????????
   *
   */
  int
  indxl2g_(const int *indxloc,
           const int *nb,
           const int *iproc,
           const int *isrcproc,
           const int *nprocs);

  /**
   * ???????????????????????????????????????
   *
   */
  void
  pdgesv_(const int *n,
          const int *nrhs,
          double *   A,
          const int *ia,
          const int *ja,
          const int *desca,
          int *      ipiv,
          double *   B,
          const int *ib,
          const int *jb,
          const int *descb,
          int *      info);
  void
  psgesv_(const int *n,
          const int *nrhs,
          float *    A,
          const int *ia,
          const int *ja,
          const int *desca,
          int *      ipiv,
          float *    B,
          const int *ib,
          const int *jb,
          const int *descb,
          int *      info);

  /**
   * ????????????-???????????????????????????
   * @f{align*}{
   * \mathrm{sub}(C) &\dealcoloneq \alpha op(\mathrm{sub}(A))op(\mathrm{sub}(B))
   *                          + \beta \mathrm{sub}(C), \\
   * \mathrm{sub}(C) &\dealcoloneq \alpha op(\mathrm{sub}(A))op(\mathrm{sub}(B))
   *                          + beta sub(C),
   * @f}
   * ?????? $\mathrm{sub}(C)$ ??????C(IC:IC+M-1,JC:JC+N-1)???????????? $op(X)$
   * ??? $op(X) = X$ ??? $op(X) = X^T$ ?????????
   *
   */
  void
  pdgemm_(const char *  transa,
          const char *  transb,
          const int *   m,
          const int *   n,
          const int *   k,
          const double *alpha,
          const double *A,
          const int *   IA,
          const int *   JA,
          const int *   DESCA,
          const double *B,
          const int *   IB,
          const int *   JB,
          const int *   DESCB,
          const double *beta,
          double *      C,
          const int *   IC,
          const int *   JC,
          const int *   DESCC);
  void
  psgemm_(const char * transa,
          const char * transb,
          const int *  m,
          const int *  n,
          const int *  k,
          const float *alpha,
          const float *A,
          const int *  IA,
          const int *  JA,
          const int *  DESCA,
          const float *B,
          const int *  IB,
          const int *  JB,
          const int *  DESCB,
          const float *beta,
          float *      C,
          const int *  IC,
          const int *  JC,
          const int *  DESCC);

  /**
   * ?????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
   *
   */
  double
  pdlange_(char const *  norm,
           const int *   m,
           const int *   n,
           const double *A,
           const int *   ia,
           const int *   ja,
           const int *   desca,
           double *      work);
  float
  pslange_(const char * norm,
           const int *  m,
           const int *  n,
           const float *A,
           const int *  ia,
           const int *  ja,
           const int *  desca,
           float *      work);

  /**
   * ???????????????????????????????????????????????????????????????????????????
   *
   */
  int
  indxg2p_(const int *glob,
           const int *nb,
           const int *iproc,
           const int *isproc,
           const int *nprocs);

  /**
   * ?????????????????????ScaLAPACK???????????????????????????????????????A?????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????http://www.netlib.org/scalapack/explore-html/d0/d1a/pdsyev_8f.html
   * https://www.ibm.com/support/knowledgecenter/SSNR5K_4.2.0/com.ibm.cluster.pessl.v4r2.pssl100.doc/am6gr_lsyev.htm#lsyev
   *
   */
  void
  pdsyev_(const char *jobz,
          const char *uplo,
          const int * m,
          double *    A,
          const int * ia,
          const int * ja,
          int *       desca,
          double *    w,
          double *    z,
          const int * iz,
          const int * jz,
          int *       descz,
          double *    work,
          const int * lwork,
          int *       info);
  void
  pssyev_(const char *jobz,
          const char *uplo,
          const int * m,
          float *     A,
          const int * ia,
          const int * ja,
          int *       desca,
          float *     w,
          float *     z,
          const int * iz,
          const int * jz,
          int *       descz,
          float *     work,
          const int * lwork,
          int *       info);

  /**
   * ????????????????????????A???????????????????????????????????????????????????B?????????????????????pdlacpy??????????????????
   * $\mathrm{sub}(A) \dealcoloneq \mathrm{sub}(B)$  ?????????
   * $\mathrm{sub}(A)$  ??????  $A(ia:ia+m-1, ja:ja+n-1)$  ???
   * $\mathrm{sub}(B)$  ??????  $B(ib:ib+m-1, jb:jb+n-1)$  ???
   *
   */
  void
  pdlacpy_(const char *  uplo,
           const int *   m,
           const int *   n,
           const double *A,
           const int *   ia,
           const int *   ja,
           const int *   desca,
           double *      B,
           const int *   ib,
           const int *   jb,
           const int *   descb);
  void
  pslacpy_(const char * uplo,
           const int *  m,
           const int *  n,
           const float *A,
           const int *  ia,
           const int *  ja,
           const int *  desca,
           float *      B,
           const int *  ib,
           const int *  jb,
           const int *  descb);

  /**
   * ?????????????????????????????? @p A
   * ?????????????????????????????????????????? @p B
   * ???????????????A???B????????????????????????????????????????????????????????????????????????????????????????????????????????????
   * @p ictxt ??????????????????????????????A???B???????????????????????????
   *
   */
  void
  pdgemr2d_(const int *   m,
            const int *   n,
            const double *A,
            const int *   ia,
            const int *   ja,
            const int *   desca,
            double *      B,
            const int *   ib,
            const int *   jb,
            const int *   descb,
            const int *   ictxt);
  void
  psgemr2d_(const int *  m,
            const int *  n,
            const float *A,
            const int *  ia,
            const int *  ja,
            const int *  desca,
            float *      B,
            const int *  ib,
            const int *  jb,
            const int *  descb,
            const int *  ictxt);

  /**
   * ?????????????????????????????????
   *
   */
  double
  pdlamch_(const int *ictxt, const char *cmach);
  float
  pslamch_(const int *ictxt, const char *cmach);


  /**
   * psyevx??????????????????????????????A?????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????/?????????
   *
   */
  void
  pdsyevx_(const char *  jobz,
           const char *  range,
           const char *  uplo,
           const int *   n,
           double *      A,
           const int *   ia,
           const int *   ja,
           const int *   desca,
           const double *VL,
           const double *VU,
           const int *   il,
           const int *   iu,
           const double *abstol,
           const int *   m,
           const int *   nz,
           double *      w,
           double *      orfac,
           double *      Z,
           const int *   iz,
           const int *   jz,
           const int *   descz,
           double *      work,
           int *         lwork,
           int *         iwork,
           int *         liwork,
           int *         ifail,
           int *         iclustr,
           double *      gap,
           int *         info);
  void
  pssyevx_(const char * jobz,
           const char * range,
           const char * uplo,
           const int *  n,
           float *      A,
           const int *  ia,
           const int *  ja,
           const int *  desca,
           const float *VL,
           const float *VU,
           const int *  il,
           const int *  iu,
           const float *abstol,
           const int *  m,
           const int *  nz,
           float *      w,
           float *      orfac,
           float *      Z,
           const int *  iz,
           const int *  jz,
           const int *  descz,
           float *      work,
           int *        lwork,
           int *        iwork,
           int *        liwork,
           int *        ifail,
           int *        iclustr,
           float *      gap,
           int *        info);

  /* PDGESVD??????M???N??????A?????????????????????SVD??????????????????????????????/??????????????????  
*
*/
  void
  pdgesvd_(const char *jobu,
           const char *jobvt,
           const int * m,
           const int * n,
           double *    A,
           const int * ia,
           const int * ja,
           const int * desca,
           double *    S,
           double *    U,
           const int * iu,
           const int * ju,
           const int * descu,
           double *    VT,
           const int * ivt,
           const int * jvt,
           const int * descvt,
           double *    work,
           int *       lwork,
           int *       info);
  void
  psgesvd_(const char *jobu,
           const char *jobvt,
           const int * m,
           const int * n,
           float *     A,
           const int * ia,
           const int * ja,
           const int * desca,
           float *     S,
           float *     U,
           const int * iu,
           const int * ju,
           const int * descu,
           float *     VT,
           const int * ivt,
           const int * jvt,
           const int * descvt,
           float *     work,
           int *       lwork,
           int *       info);

  /* P_GELS??????A???QR???LQ????????????????????????M???N??????A?????????????????????????????????????????????????????????A??????????????? 
*
*/
  void
  pdgels_(const char *trans,
          const int * m,
          const int * n,
          const int * nrhs,
          double *    A,
          const int * ia,
          const int * ja,
          const int * desca,
          double *    B,
          const int * ib,
          const int * jb,
          const int * descb,
          double *    work,
          int *       lwork,
          int *       info);
  void
  psgels_(const char *trans,
          const int * m,
          const int * n,
          const int * nrhs,
          float *     A,
          const int * ia,
          const int * ja,
          const int * desca,
          float *     B,
          const int * ib,
          const int * jb,
          const int * descb,
          float *     work,
          int *       lwork,
          int *       info);

  /* ?????????????????????  @f{equation*}{
   C \dealcoloneq \beta C + \alpha op(A),
   @f}
* ?????? $op(A)$ ?????? $op(A) = A$ ??? $op(A)=A^T$  ??? 
*
*/
  void
  pdgeadd_(const char *  transa,
           const int *   m,
           const int *   n,
           const double *alpha,
           const double *A,
           const int *   IA,
           const int *   JA,
           const int *   DESCA,
           const double *beta,
           double *      C,
           const int *   IC,
           const int *   JC,
           const int *   DESCC);
  void
  psgeadd_(const char * transa,
           const int *  m,
           const int *  n,
           const float *alpha,
           const float *A,
           const int *  IA,
           const int *  JA,
           const int *  DESCA,
           const float *beta,
           float *      C,
           const int *  IC,
           const int *  JC,
           const int *  DESCC);

  /**
   * ???????????????????????????????????????  C = beta C + alpha A^T
   *
   */
  void
  pdtran_(const int *   m,
          const int *   n,
          const double *alpha,
          const double *A,
          const int *   IA,
          const int *   JA,
          const int *   DESCA,
          const double *beta,
          double *      C,
          const int *   IC,
          const int *   JC,
          const int *   DESCC);
  void
  pstran_(const int *  m,
          const int *  n,
          const float *alpha,
          const float *A,
          const int *  IA,
          const int *  JA,
          const int *  DESCA,
          const float *beta,
          float *      C,
          const int *  IC,
          const int *  JC,
          const int *  DESCC);

  /**
   * psyevr??????MRR????????????????????????????????????????????????A??????????????????????????????????????????????????????/?????????????????????????????????????????????????????????????????????????????????
   *
   */
  void
  pdsyevr_(const char *  jobz,
           const char *  range,
           const char *  uplo,
           const int *   n,
           double *      A,
           const int *   IA,
           const int *   JA,
           const int *   DESCA,
           const double *VL,
           const double *VU,
           const int *   IL,
           const int *   IU,
           int *         m,
           int *         nz,
           double *      w,
           double *      Z,
           const int *   IZ,
           const int *   JZ,
           const int *   DESCZ,
           double *      work,
           int *         lwork,
           int *         iwork,
           int *         liwork,
           int *         info);
  void
  pssyevr_(const char * jobz,
           const char * range,
           const char * uplo,
           const int *  n,
           float *      A,
           const int *  IA,
           const int *  JA,
           const int *  DESCA,
           const float *VL,
           const float *VU,
           const int *  IL,
           const int *  IU,
           int *        m,
           int *        nz,
           float *      w,
           float *      Z,
           const int *  IZ,
           const int *  JZ,
           const int *  DESCZ,
           float *      work,
           int *        lwork,
           int *        iwork,
           int *        liwork,
           int *        info);
}



/* ?????????????????????????????????ScaLAPACK???????????????????????????????????????????????????????????????????????????????????????

* 
*
*/
template <typename number>
inline void
Cgerv2d(int  /*context*/ ,
        int  /*M*/ ,
        int  /*N*/ ,
        number *  /*A*/ ,
        int  /*lda*/ ,
        int  /*rsrc*/ ,
        int  /*csrc*/ )
{
  Assert(false, dealii::ExcNotImplemented());
}

inline void
Cgerv2d(int context, int M, int N, double *A, int lda, int rsrc, int csrc)
{
  Cdgerv2d(context, M, N, A, lda, rsrc, csrc);
}

inline void
Cgerv2d(int context, int M, int N, float *A, int lda, int rsrc, int csrc)
{
  Csgerv2d(context, M, N, A, lda, rsrc, csrc);
}


template <typename number>
inline void
Cgesd2d(int  /*context*/ ,
        int  /*M*/ ,
        int  /*N*/ ,
        number *  /*A*/ ,
        int  /*lda*/ ,
        int  /*rdest*/ ,
        int  /*cdest*/ )
{
  Assert(false, dealii::ExcNotImplemented());
}

inline void
Cgesd2d(int context, int M, int N, double *A, int lda, int rdest, int cdest)
{
  Cdgesd2d(context, M, N, A, lda, rdest, cdest);
}

inline void
Cgesd2d(int context, int M, int N, float *A, int lda, int rdest, int cdest)
{
  Csgesd2d(context, M, N, A, lda, rdest, cdest);
}


template <typename number>
inline void
ppotrf(const char *  /*UPLO*/ ,
       const int *  /*N*/ ,
       number *  /*A*/ ,
       const int *  /*IA*/ ,
       const int *  /*JA*/ ,
       const int *  /*DESCA*/ ,
       int *  /*INFO*/ )
{
  Assert(false, dealii::ExcNotImplemented());
}

inline void
ppotrf(const char *UPLO,
       const int * N,
       double *    A,
       const int * IA,
       const int * JA,
       const int * DESCA,
       int *       INFO)
{
  pdpotrf_(UPLO, N, A, IA, JA, DESCA, INFO);
}

inline void
ppotrf(const char *UPLO,
       const int * N,
       float *     A,
       const int * IA,
       const int * JA,
       const int * DESCA,
       int *       INFO)
{
  pspotrf_(UPLO, N, A, IA, JA, DESCA, INFO);
}


template <typename number>
inline void
pgetrf(const int *  /*m*/ ,
       const int *  /*n*/ ,
       number *  /*A*/ ,
       const int *  /*IA*/ ,
       const int *  /*JA*/ ,
       const int *  /*DESCA*/ ,
       int *  /*ipiv*/ ,
       int *  /*INFO*/ )
{
  Assert(false, dealii::ExcNotImplemented());
}

inline void
pgetrf(const int *m,
       const int *n,
       double *   A,
       const int *IA,
       const int *JA,
       const int *DESCA,
       int *      ipiv,
       int *      INFO)
{
  pdgetrf_(m, n, A, IA, JA, DESCA, ipiv, INFO);
}

inline void
pgetrf(const int *m,
       const int *n,
       float *    A,
       const int *IA,
       const int *JA,
       const int *DESCA,
       int *      ipiv,
       int *      INFO)
{
  psgetrf_(m, n, A, IA, JA, DESCA, ipiv, INFO);
}


template <typename number>
inline void
ppotri(const char *  /*UPLO*/ ,
       const int *  /*N*/ ,
       number *  /*A*/ ,
       const int *  /*IA*/ ,
       const int *  /*JA*/ ,
       const int *  /*DESCA*/ ,
       int *  /*INFO*/ )
{
  Assert(false, dealii::ExcNotImplemented());
}

inline void
ppotri(const char *UPLO,
       const int * N,
       double *    A,
       const int * IA,
       const int * JA,
       const int * DESCA,
       int *       INFO)
{
  pdpotri_(UPLO, N, A, IA, JA, DESCA, INFO);
}

inline void
ppotri(const char *UPLO,
       const int * N,
       float *     A,
       const int * IA,
       const int * JA,
       const int * DESCA,
       int *       INFO)
{
  pspotri_(UPLO, N, A, IA, JA, DESCA, INFO);
}


template <typename number>
inline void
pgetri(const int *  /*N*/ ,
       number *  /*A*/ ,
       const int *  /*IA*/ ,
       const int *  /*JA*/ ,
       const int *  /*DESCA*/ ,
       const int *  /*ipiv*/ ,
       number *  /*work*/ ,
       int *  /*lwork*/ ,
       int *  /*iwork*/ ,
       int *  /*liwork*/ ,
       int *  /*info*/ )
{
  Assert(false, dealii::ExcNotImplemented());
}

inline void
pgetri(const int *N,
       double *   A,
       const int *IA,
       const int *JA,
       const int *DESCA,
       const int *ipiv,
       double *   work,
       int *      lwork,
       int *      iwork,
       int *      liwork,
       int *      info)
{
  pdgetri_(N, A, IA, JA, DESCA, ipiv, work, lwork, iwork, liwork, info);
}

inline void
pgetri(const int *N,
       float *    A,
       const int *IA,
       const int *JA,
       const int *DESCA,
       const int *ipiv,
       float *    work,
       int *      lwork,
       int *      iwork,
       int *      liwork,
       int *      info)
{
  psgetri_(N, A, IA, JA, DESCA, ipiv, work, lwork, iwork, liwork, info);
}

template <typename number>
inline void
ptrtri(const char *  /*UPLO*/ ,
       const char *  /*DIAG*/ ,
       const int *  /*N*/ ,
       number *  /*A*/ ,
       const int *  /*IA*/ ,
       const int *  /*JA*/ ,
       const int *  /*DESCA*/ ,
       int *  /*INFO*/ )
{
  Assert(false, dealii::ExcNotImplemented());
}

inline void
ptrtri(const char *UPLO,
       const char *DIAG,
       const int * N,
       double *    A,
       const int * IA,
       const int * JA,
       const int * DESCA,
       int *       INFO)
{
  pdtrtri_(UPLO, DIAG, N, A, IA, JA, DESCA, INFO);
}

inline void
ptrtri(const char *UPLO,
       const char *DIAG,
       const int * N,
       float *     A,
       const int * IA,
       const int * JA,
       const int * DESCA,
       int *       INFO)
{
  pstrtri_(UPLO, DIAG, N, A, IA, JA, DESCA, INFO);
}

template <typename number>
inline void
ppocon(const char *  /*uplo*/ ,
       const int *  /*N*/ ,
       const number *  /*A*/ ,
       const int *  /*IA*/ ,
       const int *  /*JA*/ ,
       const int *  /*DESCA*/ ,
       const number *  /*ANORM*/ ,
       number *  /*RCOND*/ ,
       number *  /*WORK*/ ,
       const int *  /*LWORK*/ ,
       int *  /*IWORK*/ ,
       const int *  /*LIWORK*/ ,
       int *  /*INFO*/ )
{
  Assert(false, dealii::ExcNotImplemented());
}

inline void
ppocon(const char *  uplo,
       const int *   N,
       const double *A,
       const int *   IA,
       const int *   JA,
       const int *   DESCA,
       const double *ANORM,
       double *      RCOND,
       double *      WORK,
       const int *   LWORK,
       int *         IWORK,
       const int *   LIWORK,
       int *         INFO)
{
  pdpocon_(
    uplo, N, A, IA, JA, DESCA, ANORM, RCOND, WORK, LWORK, IWORK, LIWORK, INFO);
}

inline void
ppocon(const char * uplo,
       const int *  N,
       const float *A,
       const int *  IA,
       const int *  JA,
       const int *  DESCA,
       const float *ANORM,
       float *      RCOND,
       float *      WORK,
       const int *  LWORK,
       int *        IWORK,
       const int *  LIWORK,
       int *        INFO)
{
  pspocon_(
    uplo, N, A, IA, JA, DESCA, ANORM, RCOND, WORK, LWORK, IWORK, LIWORK, INFO);
}


template <typename number>
inline number
plansy(const char *  /*norm*/ ,
       const char *  /*uplo*/ ,
       const int *  /*N*/ ,
       const number *  /*A*/ ,
       const int *  /*IA*/ ,
       const int *  /*JA*/ ,
       const int *  /*DESCA*/ ,
       number *  /*work*/ )
{
  Assert(false, dealii::ExcNotImplemented());
}

inline double
plansy(const char *  norm,
       const char *  uplo,
       const int *   N,
       const double *A,
       const int *   IA,
       const int *   JA,
       const int *   DESCA,
       double *      work)
{
  return pdlansy_(norm, uplo, N, A, IA, JA, DESCA, work);
}

inline float
plansy(const char * norm,
       const char * uplo,
       const int *  N,
       const float *A,
       const int *  IA,
       const int *  JA,
       const int *  DESCA,
       float *      work)
{
  return pslansy_(norm, uplo, N, A, IA, JA, DESCA, work);
}


template <typename number>
inline void
pgesv(const int *  /*n*/ ,
      const int *  /*nrhs*/ ,
      number *  /*A*/ ,
      const int *  /*ia*/ ,
      const int *  /*ja*/ ,
      const int *  /*desca*/ ,
      int *  /*ipiv*/ ,
      number *  /*B*/ ,
      const int *  /*ib*/ ,
      const int *  /*jb*/ ,
      const int *  /*descb*/ ,
      int *  /*info*/ )
{
  Assert(false, dealii::ExcNotImplemented());
}

inline void
pgesv(const int *n,
      const int *nrhs,
      double *   A,
      const int *ia,
      const int *ja,
      const int *desca,
      int *      ipiv,
      double *   B,
      const int *ib,
      const int *jb,
      const int *descb,
      int *      info)
{
  pdgesv_(n, nrhs, A, ia, ja, desca, ipiv, B, ib, jb, descb, info);
}

inline void
pgesv(const int *n,
      const int *nrhs,
      float *    A,
      const int *ia,
      const int *ja,
      const int *desca,
      int *      ipiv,
      float *    B,
      const int *ib,
      const int *jb,
      const int *descb,
      int *      info)
{
  psgesv_(n, nrhs, A, ia, ja, desca, ipiv, B, ib, jb, descb, info);
}


template <typename number>
inline void
pgemm(const char *  /*transa*/ ,
      const char *  /*transb*/ ,
      const int *  /*m*/ ,
      const int *  /*n*/ ,
      const int *  /*k*/ ,
      const number *  /*alpha*/ ,
      number *  /*A*/ ,
      const int *  /*IA*/ ,
      const int *  /*JA*/ ,
      const int *  /*DESCA*/ ,
      number *  /*B*/ ,
      const int *  /*IB*/ ,
      const int *  /*JB*/ ,
      const int *  /*DESCB*/ ,
      const number *  /*beta*/ ,
      number *  /*C*/ ,
      const int *  /*IC*/ ,
      const int *  /*JC*/ ,
      const int *  /*DESCC*/ )
{
  Assert(false, dealii::ExcNotImplemented());
}

inline void
pgemm(const char *  transa,
      const char *  transb,
      const int *   m,
      const int *   n,
      const int *   k,
      const double *alpha,
      const double *A,
      const int *   IA,
      const int *   JA,
      const int *   DESCA,
      const double *B,
      const int *   IB,
      const int *   JB,
      const int *   DESCB,
      const double *beta,
      double *      C,
      const int *   IC,
      const int *   JC,
      const int *   DESCC)
{
  pdgemm_(transa,
          transb,
          m,
          n,
          k,
          alpha,
          A,
          IA,
          JA,
          DESCA,
          B,
          IB,
          JB,
          DESCB,
          beta,
          C,
          IC,
          JC,
          DESCC);
}

inline void
pgemm(const char * transa,
      const char * transb,
      const int *  m,
      const int *  n,
      const int *  k,
      const float *alpha,
      const float *A,
      const int *  IA,
      const int *  JA,
      const int *  DESCA,
      const float *B,
      const int *  IB,
      const int *  JB,
      const int *  DESCB,
      const float *beta,
      float *      C,
      const int *  IC,
      const int *  JC,
      const int *  DESCC)
{
  psgemm_(transa,
          transb,
          m,
          n,
          k,
          alpha,
          A,
          IA,
          JA,
          DESCA,
          B,
          IB,
          JB,
          DESCB,
          beta,
          C,
          IC,
          JC,
          DESCC);
}


template <typename number>
inline number
plange(const char *  /*norm*/ ,
       const int *  /*m*/ ,
       const int *  /*n*/ ,
       const number *  /*A*/ ,
       const int *  /*ia*/ ,
       const int *  /*ja*/ ,
       const int *  /*desca*/ ,
       number *  /*work*/ )
{
  Assert(false, dealii::ExcNotImplemented());
}

inline double
plange(const char *  norm,
       const int *   m,
       const int *   n,
       const double *A,
       const int *   ia,
       const int *   ja,
       const int *   desca,
       double *      work)
{
  return pdlange_(norm, m, n, A, ia, ja, desca, work);
}

inline float
plange(const char * norm,
       const int *  m,
       const int *  n,
       const float *A,
       const int *  ia,
       const int *  ja,
       const int *  desca,
       float *      work)
{
  return pslange_(norm, m, n, A, ia, ja, desca, work);
}


template <typename number>
inline void
psyev(const char *  /*jobz*/ ,
      const char *  /*uplo*/ ,
      const int *  /*m*/ ,
      number *  /*A*/ ,
      const int *  /*ia*/ ,
      const int *  /*ja*/ ,
      int *  /*desca*/ ,
      number *  /*w*/ ,
      number *  /*z*/ ,
      const int *  /*iz*/ ,
      const int *  /*jz*/ ,
      int *  /*descz*/ ,
      number *  /*work*/ ,
      const int *  /*lwork*/ ,
      int *  /*info*/ )
{
  Assert(false, dealii::ExcNotImplemented());
}

inline void
psyev(const char *jobz,
      const char *uplo,
      const int * m,
      double *    A,
      const int * ia,
      const int * ja,
      int *       desca,
      double *    w,
      double *    z,
      const int * iz,
      const int * jz,
      int *       descz,
      double *    work,
      const int * lwork,
      int *       info)
{
  pdsyev_(
    jobz, uplo, m, A, ia, ja, desca, w, z, iz, jz, descz, work, lwork, info);
}

inline void
psyev(const char *jobz,
      const char *uplo,
      const int * m,
      float *     A,
      const int * ia,
      const int * ja,
      int *       desca,
      float *     w,
      float *     z,
      const int * iz,
      const int * jz,
      int *       descz,
      float *     work,
      const int * lwork,
      int *       info)
{
  pssyev_(
    jobz, uplo, m, A, ia, ja, desca, w, z, iz, jz, descz, work, lwork, info);
}


template <typename number>
inline void
placpy(const char *  /*uplo*/ ,
       const int *  /*m*/ ,
       const int *  /*n*/ ,
       const number *  /*A*/ ,
       const int *  /*ia*/ ,
       const int *  /*ja*/ ,
       const int *  /*desca*/ ,
       number *  /*B*/ ,
       const int *  /*ib*/ ,
       const int *  /*jb*/ ,
       const int *  /*descb*/ )
{
  Assert(false, dealii::ExcNotImplemented());
}

inline void
placpy(const char *  uplo,
       const int *   m,
       const int *   n,
       const double *A,
       const int *   ia,
       const int *   ja,
       const int *   desca,
       double *      B,
       const int *   ib,
       const int *   jb,
       const int *   descb)
{
  pdlacpy_(uplo, m, n, A, ia, ja, desca, B, ib, jb, descb);
}

inline void
placpy(const char * uplo,
       const int *  m,
       const int *  n,
       const float *A,
       const int *  ia,
       const int *  ja,
       const int *  desca,
       float *      B,
       const int *  ib,
       const int *  jb,
       const int *  descb)
{
  pslacpy_(uplo, m, n, A, ia, ja, desca, B, ib, jb, descb);
}


template <typename number>
inline void
pgemr2d(const int *  /*m*/ ,
        const int *  /*n*/ ,
        const number *  /*A*/ ,
        const int *  /*ia*/ ,
        const int *  /*ja*/ ,
        const int *  /*desca*/ ,
        number *  /*B*/ ,
        const int *  /*ib*/ ,
        const int *  /*jb*/ ,
        const int *  /*descb*/ ,
        const int *  /*ictxt*/ )
{
  Assert(false, dealii::ExcNotImplemented());
}

inline void
pgemr2d(const int *   m,
        const int *   n,
        const double *A,
        const int *   ia,
        const int *   ja,
        const int *   desca,
        double *      B,
        const int *   ib,
        const int *   jb,
        const int *   descb,
        const int *   ictxt)
{
  pdgemr2d_(m, n, A, ia, ja, desca, B, ib, jb, descb, ictxt);
}

inline void
pgemr2d(const int *  m,
        const int *  n,
        const float *A,
        const int *  ia,
        const int *  ja,
        const int *  desca,
        float *      B,
        const int *  ib,
        const int *  jb,
        const int *  descb,
        const int *  ictxt)
{
  psgemr2d_(m, n, A, ia, ja, desca, B, ib, jb, descb, ictxt);
}


template <typename number>
inline void
plamch(const int *  /*ictxt*/, const char * /*cmach*/, number & /*val*/ )
{
  Assert(false, dealii::ExcNotImplemented());
}

inline void
plamch(const int *ictxt, const char *cmach, double &val)
{
  val = pdlamch_(ictxt, cmach);
}

inline void
plamch(const int *ictxt, const char *cmach, float &val)
{
  val = pslamch_(ictxt, cmach);
}


template <typename number>
inline void
psyevx(const char *  /*jobz*/ ,
       const char *  /*range*/ ,
       const char *  /*uplo*/ ,
       const int *  /*n*/ ,
       number *  /*A*/ ,
       const int *  /*ia*/ ,
       const int *  /*ja*/ ,
       const int *  /*desca*/ ,
       number *  /*VL*/ ,
       number *  /*VU*/ ,
       const int *  /*il*/ ,
       const int *  /*iu*/ ,
       number *  /*abstol*/ ,
       const int *  /*m*/ ,
       const int *  /*nz*/ ,
       number *  /*w*/ ,
       number *  /*orfac*/ ,
       number *  /*Z*/ ,
       const int *  /*iz*/ ,
       const int *  /*jz*/ ,
       const int *  /*descz*/ ,
       number *  /*work*/ ,
       int *  /*lwork*/ ,
       int *  /*iwork*/ ,
       int *  /*liwork*/ ,
       int *  /*ifail*/ ,
       int *  /*iclustr*/ ,
       number *  /*gap*/ ,
       int *  /*info*/ )
{
  Assert(false, dealii::ExcNotImplemented());
}

inline void
psyevx(const char *jobz,
       const char *range,
       const char *uplo,
       const int * n,
       double *    A,
       const int * ia,
       const int * ja,
       const int * desca,
       double *    VL,
       double *    VU,
       const int * il,
       const int * iu,
       double *    abstol,
       const int * m,
       const int * nz,
       double *    w,
       double *    orfac,
       double *    Z,
       const int * iz,
       const int * jz,
       const int * descz,
       double *    work,
       int *       lwork,
       int *       iwork,
       int *       liwork,
       int *       ifail,
       int *       iclustr,
       double *    gap,
       int *       info)
{
  pdsyevx_(jobz,
           range,
           uplo,
           n,
           A,
           ia,
           ja,
           desca,
           VL,
           VU,
           il,
           iu,
           abstol,
           m,
           nz,
           w,
           orfac,
           Z,
           iz,
           jz,
           descz,
           work,
           lwork,
           iwork,
           liwork,
           ifail,
           iclustr,
           gap,
           info);
}

inline void
psyevx(const char *jobz,
       const char *range,
       const char *uplo,
       const int * n,
       float *     A,
       const int * ia,
       const int * ja,
       const int * desca,
       float *     VL,
       float *     VU,
       const int * il,
       const int * iu,
       float *     abstol,
       const int * m,
       const int * nz,
       float *     w,
       float *     orfac,
       float *     Z,
       const int * iz,
       const int * jz,
       const int * descz,
       float *     work,
       int *       lwork,
       int *       iwork,
       int *       liwork,
       int *       ifail,
       int *       iclustr,
       float *     gap,
       int *       info)
{
  pssyevx_(jobz,
           range,
           uplo,
           n,
           A,
           ia,
           ja,
           desca,
           VL,
           VU,
           il,
           iu,
           abstol,
           m,
           nz,
           w,
           orfac,
           Z,
           iz,
           jz,
           descz,
           work,
           lwork,
           iwork,
           liwork,
           ifail,
           iclustr,
           gap,
           info);
}


template <typename number>
inline void
pgesvd(const char *  /*jobu*/ ,
       const char *  /*jobvt*/ ,
       const int *  /*m*/ ,
       const int *  /*n*/ ,
       number *  /*A*/ ,
       const int *  /*ia*/ ,
       const int *  /*ja*/ ,
       const int *  /*desca*/ ,
       number *  /*S*/ ,
       number *  /*U*/ ,
       const int *  /*iu*/ ,
       const int *  /*ju*/ ,
       const int *  /*descu*/ ,
       number *  /*VT*/ ,
       const int *  /*ivt*/ ,
       const int *  /*jvt*/ ,
       const int *  /*descvt*/ ,
       number *  /*work*/ ,
       int *  /*lwork*/ ,
       int *  /*info*/ )
{
  Assert(false, dealii::ExcNotImplemented());
}

inline void
pgesvd(const char *jobu,
       const char *jobvt,
       const int * m,
       const int * n,
       double *    A,
       const int * ia,
       const int * ja,
       const int * desca,
       double *    S,
       double *    U,
       const int * iu,
       const int * ju,
       const int * descu,
       double *    VT,
       const int * ivt,
       const int * jvt,
       const int * descvt,
       double *    work,
       int *       lwork,
       int *       info)
{
  pdgesvd_(jobu,
           jobvt,
           m,
           n,
           A,
           ia,
           ja,
           desca,
           S,
           U,
           iu,
           ju,
           descu,
           VT,
           ivt,
           jvt,
           descvt,
           work,
           lwork,
           info);
}

inline void
pgesvd(const char *jobu,
       const char *jobvt,
       const int * m,
       const int * n,
       float *     A,
       const int * ia,
       const int * ja,
       const int * desca,
       float *     S,
       float *     U,
       const int * iu,
       const int * ju,
       const int * descu,
       float *     VT,
       const int * ivt,
       const int * jvt,
       const int * descvt,
       float *     work,
       int *       lwork,
       int *       info)
{
  psgesvd_(jobu,
           jobvt,
           m,
           n,
           A,
           ia,
           ja,
           desca,
           S,
           U,
           iu,
           ju,
           descu,
           VT,
           ivt,
           jvt,
           descvt,
           work,
           lwork,
           info);
}


template <typename number>
inline void
pgels(const char *  /*trans*/ ,
      const int *  /*m*/ ,
      const int *  /*n*/ ,
      const int *  /*nrhs*/ ,
      number *  /*A*/ ,
      const int *  /*ia*/ ,
      const int *  /*ja*/ ,
      const int *  /*desca*/ ,
      number *  /*B*/ ,
      const int *  /*ib*/ ,
      const int *  /*jb*/ ,
      const int *  /*descb*/ ,
      number *  /*work*/ ,
      int *  /*lwork*/ ,
      int *  /*info*/ )
{
  Assert(false, dealii::ExcNotImplemented());
}

inline void
pgels(const char *trans,
      const int * m,
      const int * n,
      const int * nrhs,
      double *    A,
      const int * ia,
      const int * ja,
      const int * desca,
      double *    B,
      const int * ib,
      const int * jb,
      const int * descb,
      double *    work,
      int *       lwork,
      int *       info)
{
  pdgels_(
    trans, m, n, nrhs, A, ia, ja, desca, B, ib, jb, descb, work, lwork, info);
}

inline void
pgels(const char *trans,
      const int * m,
      const int * n,
      const int * nrhs,
      float *     A,
      const int * ia,
      const int * ja,
      const int * desca,
      float *     B,
      const int * ib,
      const int * jb,
      const int * descb,
      float *     work,
      int *       lwork,
      int *       info)
{
  psgels_(
    trans, m, n, nrhs, A, ia, ja, desca, B, ib, jb, descb, work, lwork, info);
}


template <typename number>
inline void
pgeadd(const char *  /*transa*/ ,
       const int *  /*m*/ ,
       const int *  /*n*/ ,
       const number *  /*alpha*/ ,
       const number *  /*A*/ ,
       const int *  /*IA*/ ,
       const int *  /*JA*/ ,
       const int *  /*DESCA*/ ,
       const number *  /*beta*/ ,
       number *  /*C*/ ,
       const int *  /*IC*/ ,
       const int *  /*JC*/ ,
       const int *  /*DESCC*/ )
{
  Assert(false, dealii::ExcNotImplemented());
}

inline void
pgeadd(const char *  transa,
       const int *   m,
       const int *   n,
       const double *alpha,
       const double *A,
       const int *   IA,
       const int *   JA,
       const int *   DESCA,
       const double *beta,
       double *      C,
       const int *   IC,
       const int *   JC,
       const int *   DESCC)
{
  pdgeadd_(transa, m, n, alpha, A, IA, JA, DESCA, beta, C, IC, JC, DESCC);
}

inline void
pgeadd(const char * transa,
       const int *  m,
       const int *  n,
       const float *alpha,
       const float *A,
       const int *  IA,
       const int *  JA,
       const int *  DESCA,
       const float *beta,
       float *      C,
       const int *  IC,
       const int *  JC,
       const int *  DESCC)
{
  psgeadd_(transa, m, n, alpha, A, IA, JA, DESCA, beta, C, IC, JC, DESCC);
}


template <typename number>
inline void
ptran(const int *  /*m*/ ,
      const int *  /*n*/ ,
      const number *  /*alpha*/ ,
      const number *  /*A*/ ,
      const int *  /*IA*/ ,
      const int *  /*JA*/ ,
      const int *  /*DESCA*/ ,
      const number *  /*beta*/ ,
      number *  /*C*/ ,
      const int *  /*IC*/ ,
      const int *  /*JC*/ ,
      const int *  /*DESCC*/ )
{
  Assert(false, dealii::ExcNotImplemented());
}

inline void
ptran(const int *   m,
      const int *   n,
      const double *alpha,
      const double *A,
      const int *   IA,
      const int *   JA,
      const int *   DESCA,
      const double *beta,
      double *      C,
      const int *   IC,
      const int *   JC,
      const int *   DESCC)
{
  pdtran_(m, n, alpha, A, IA, JA, DESCA, beta, C, IC, JC, DESCC);
}

inline void
ptran(const int *  m,
      const int *  n,
      const float *alpha,
      const float *A,
      const int *  IA,
      const int *  JA,
      const int *  DESCA,
      const float *beta,
      float *      C,
      const int *  IC,
      const int *  JC,
      const int *  DESCC)
{
  pstran_(m, n, alpha, A, IA, JA, DESCA, beta, C, IC, JC, DESCC);
}


template <typename number>
inline void
psyevr(const char *  /*jobz*/ ,
       const char *  /*range*/ ,
       const char *  /*uplo*/ ,
       const int *  /*n*/ ,
       number *  /*A*/ ,
       const int *  /*IA*/ ,
       const int *  /*JA*/ ,
       const int *  /*DESCA*/ ,
       const number *  /*VL*/ ,
       const number *  /*VU*/ ,
       const int *  /*IL*/ ,
       const int *  /*IU*/ ,
       int *  /*m*/ ,
       int *  /*nz*/ ,
       number *  /*w*/ ,
       number *  /*Z*/ ,
       const int *  /*IZ*/ ,
       const int *  /*JZ*/ ,
       const int *  /*DESCZ*/ ,
       number *  /*work*/ ,
       int *  /*lwork*/ ,
       int *  /*iwork*/ ,
       int *  /*liwork*/ ,
       int *  /*info*/ )
{
  Assert(false, dealii::ExcNotImplemented());
}

inline void
psyevr(const char *  jobz,
       const char *  range,
       const char *  uplo,
       const int *   n,
       double *      A,
       const int *   IA,
       const int *   JA,
       const int *   DESCA,
       const double *VL,
       const double *VU,
       const int *   IL,
       const int *   IU,
       int *         m,
       int *         nz,
       double *      w,
       double *      Z,
       const int *   IZ,
       const int *   JZ,
       const int *   DESCZ,
       double *      work,
       int *         lwork,
       int *         iwork,
       int *         liwork,
       int *         info)
{
  /* Netlib ScaLAPACK?????????pdsyevr??????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????pdsyevr??????????????????????????????????????????????????? 
*
*/
#  ifdef DEAL_II_HAVE_FP_EXCEPTIONS
  fenv_t fp_exceptions;
  feholdexcept(&fp_exceptions);
#  endif

  pdsyevr_(jobz,
           range,
           uplo,
           n,
           A,
           IA,
           JA,
           DESCA,
           VL,
           VU,
           IL,
           IU,
           m,
           nz,
           w,
           Z,
           IZ,
           JZ,
           DESCZ,
           work,
           lwork,
           iwork,
           liwork,
           info);

#  ifdef DEAL_II_HAVE_FP_EXCEPTIONS
  fesetenv(&fp_exceptions);
#  endif
}

inline void
psyevr(const char * jobz,
       const char * range,
       const char * uplo,
       const int *  n,
       float *      A,
       const int *  IA,
       const int *  JA,
       const int *  DESCA,
       const float *VL,
       const float *VU,
       const int *  IL,
       const int *  IU,
       int *        m,
       int *        nz,
       float *      w,
       float *      Z,
       const int *  IZ,
       const int *  JZ,
       const int *  DESCZ,
       float *      work,
       int *        lwork,
       int *        iwork,
       int *        liwork,
       int *        info)
{
  /* Netlib ScaLAPACK?????????pssyevr??????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????pssyevr??????????????????????????????????????????????????? 
*
*/
#  ifdef DEAL_II_HAVE_FP_EXCEPTIONS
  fenv_t fp_exceptions;
  feholdexcept(&fp_exceptions);
#  endif

  pssyevr_(jobz,
           range,
           uplo,
           n,
           A,
           IA,
           JA,
           DESCA,
           VL,
           VU,
           IL,
           IU,
           m,
           nz,
           w,
           Z,
           IZ,
           JZ,
           DESCZ,
           work,
           lwork,
           iwork,
           liwork,
           info);

#  ifdef DEAL_II_HAVE_FP_EXCEPTIONS
  fesetenv(&fp_exceptions);
#  endif
}

#endif // DEAL_II_WITH_SCALAPACK

#endif // dealii_scalapack_templates_h


