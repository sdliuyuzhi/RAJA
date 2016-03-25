//AUTOGENERATED BY genForallN.py
/*
 * Copyright (c) 2016, Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 *
 * All rights reserved.
 *
 * This source code cannot be distributed without permission and
 * further review from Lawrence Livermore National Laboratory.
 */
  
#ifndef RAJA_DOMAIN_FORALL3_HXX__
#define RAJA_DOMAIN_FORALL3_HXX__

#include<RAJA/RAJA.hxx>
#include<RAJA/Tile.hxx>

namespace RAJA {



/******************************************************************
 *  Policy base class, forall3()
 ******************************************************************/

// Execute (Termination default)
struct Forall3_Execute_Tag {};
struct Forall3_Execute {
  typedef Forall3_Execute_Tag PolicyTag;
};

// Starting (outer) policy for all forall3 policies
template<typename POL_I=RAJA::seq_exec, typename POL_J=RAJA::seq_exec, typename POL_K=RAJA::seq_exec, typename NEXT=Forall3_Execute>
struct Forall3_Policy {
  typedef NEXT NextPolicy;
  typedef POL_I PolicyI;
  typedef POL_J PolicyJ;
  typedef POL_K PolicyK;
};

// Interchange loop order given permutation
struct Forall3_Permute_Tag {};
template<typename LOOP_ORDER, typename NEXT=Forall3_Execute>
struct Forall3_Permute {
  typedef Forall3_Permute_Tag PolicyTag;
  typedef NEXT NextPolicy;
  typedef LOOP_ORDER LoopOrder;
};

// Begin OpenMP Parallel Region
struct Forall3_OMP_Parallel_Tag {};
template<typename NEXT=Forall3_Execute>
struct Forall3_OMP_Parallel {
  typedef Forall3_OMP_Parallel_Tag PolicyTag;
  typedef NEXT NextPolicy;
};

// Tiling Policy
struct Forall3_Tile_Tag {};
template<typename TILE_I, typename TILE_J, typename TILE_K, typename NEXT=Forall3_Execute>
struct Forall3_Tile {
  typedef Forall3_Tile_Tag PolicyTag;
  typedef NEXT NextPolicy;
  typedef TILE_I TileI;
  typedef TILE_J TileJ;
  typedef TILE_K TileK;
};


/******************************************************************
 *  forall3_policy() Foreward declarations
 ******************************************************************/

template<typename POLICY, typename PolicyI, typename PolicyJ, typename PolicyK, typename TI, typename TJ, typename TK, typename BODY>
RAJA_INLINE void forall3_policy(Forall3_Execute_Tag, TI const &is_i, TJ const &is_j, TK const &is_k, BODY body);

template<typename POLICY, typename PolicyI, typename PolicyJ, typename PolicyK, typename TI, typename TJ, typename TK, typename BODY>
RAJA_INLINE void forall3_policy(Forall3_Permute_Tag, TI const &is_i, TJ const &is_j, TK const &is_k, BODY body);

template<typename POLICY, typename PolicyI, typename PolicyJ, typename PolicyK, typename TI, typename TJ, typename TK, typename BODY>
RAJA_INLINE void forall3_policy(Forall3_OMP_Parallel_Tag, TI const &is_i, TJ const &is_j, TK const &is_k, BODY body);

template<typename POLICY, typename PolicyI, typename PolicyJ, typename PolicyK, typename TI, typename TJ, typename TK, typename BODY>
RAJA_INLINE void forall3_policy(Forall3_Tile_Tag, TI const &is_i, TJ const &is_j, TK const &is_k, BODY body);


/******************************************************************
 *  Forall3Executor(): Default Executor for loops
 ******************************************************************/

template<typename POLICY_I, typename POLICY_J, typename POLICY_K, typename TI, typename TJ, typename TK>
struct Forall3Executor {
  template<typename BODY>
  inline void operator()(TI const &is_i, TJ const &is_j, TK const &is_k, BODY body) const {
    RAJA::forall<POLICY_I>(is_i, [=](Index_type i){
      exec(is_j, is_k, [=](Index_type j, Index_type k){
        body(i, j, k);
      });
    });
  }

  private:
    Forall2Executor<POLICY_J, POLICY_K, TJ, TK> exec;
};


/******************************************************************
 *  OpenMP Auto-Collapsing Executors for forall3()
 ******************************************************************/

#ifdef _OPENMP

// OpenMP Executor with collapse(2) for omp_parallel_for_exec
template<typename POLICY_K, typename TK>
class Forall3Executor<RAJA::omp_parallel_for_exec, RAJA::omp_parallel_for_exec, POLICY_K, RAJA::RangeSegment, RAJA::RangeSegment, TK> {
  public:  
    template<typename BODY>
    inline void operator()(RAJA::RangeSegment const &is_i, RAJA::RangeSegment const &is_j, TK const &is_k, BODY body) const {
      Index_type const i_start = is_i.getBegin();
      Index_type const i_end   = is_i.getEnd();

      Index_type const j_start = is_j.getBegin();
      Index_type const j_end   = is_j.getEnd();

#pragma omp parallel for schedule(static) collapse(2)
      for(Index_type i = i_start;i < i_end;++ i){
        for(Index_type j = j_start;j < j_end;++ j){
          RAJA::forall<POLICY_K>(is_k, [=](Index_type k){
            body(i, j, k);
          });
      } } 
    }
};

// OpenMP Executor with collapse(3) for omp_parallel_for_exec
template<>
class Forall3Executor<RAJA::omp_parallel_for_exec, RAJA::omp_parallel_for_exec, RAJA::omp_parallel_for_exec, RAJA::RangeSegment, RAJA::RangeSegment, RAJA::RangeSegment> {
  public:  
    template<typename BODY>
    inline void operator()(RAJA::RangeSegment const &is_i, RAJA::RangeSegment const &is_j, RAJA::RangeSegment const &is_k, BODY body) const {
      Index_type const i_start = is_i.getBegin();
      Index_type const i_end   = is_i.getEnd();

      Index_type const j_start = is_j.getBegin();
      Index_type const j_end   = is_j.getEnd();

      Index_type const k_start = is_k.getBegin();
      Index_type const k_end   = is_k.getEnd();

#pragma omp parallel for schedule(static) collapse(3)
      for(Index_type i = i_start;i < i_end;++ i){
        for(Index_type j = j_start;j < j_end;++ j){
          for(Index_type k = k_start;k < k_end;++ k){
            body(i, j, k);
      } } } 
    }
};

// OpenMP Executor with collapse(2) for omp_for_nowait_exec
template<typename POLICY_K, typename TK>
class Forall3Executor<RAJA::omp_for_nowait_exec, RAJA::omp_for_nowait_exec, POLICY_K, RAJA::RangeSegment, RAJA::RangeSegment, TK> {
  public:  
    template<typename BODY>
    inline void operator()(RAJA::RangeSegment const &is_i, RAJA::RangeSegment const &is_j, TK const &is_k, BODY body) const {
      Index_type const i_start = is_i.getBegin();
      Index_type const i_end   = is_i.getEnd();

      Index_type const j_start = is_j.getBegin();
      Index_type const j_end   = is_j.getEnd();

#pragma omp for schedule(static) collapse(2) nowait
      for(Index_type i = i_start;i < i_end;++ i){
        for(Index_type j = j_start;j < j_end;++ j){
          RAJA::forall<POLICY_K>(is_k, [=](Index_type k){
            body(i, j, k);
          });
      } } 
    }
};

// OpenMP Executor with collapse(3) for omp_for_nowait_exec
template<>
class Forall3Executor<RAJA::omp_for_nowait_exec, RAJA::omp_for_nowait_exec, RAJA::omp_for_nowait_exec, RAJA::RangeSegment, RAJA::RangeSegment, RAJA::RangeSegment> {
  public:  
    template<typename BODY>
    inline void operator()(RAJA::RangeSegment const &is_i, RAJA::RangeSegment const &is_j, RAJA::RangeSegment const &is_k, BODY body) const {
      Index_type const i_start = is_i.getBegin();
      Index_type const i_end   = is_i.getEnd();

      Index_type const j_start = is_j.getBegin();
      Index_type const j_end   = is_j.getEnd();

      Index_type const k_start = is_k.getBegin();
      Index_type const k_end   = is_k.getEnd();

#pragma omp for schedule(static) collapse(3) nowait
      for(Index_type i = i_start;i < i_end;++ i){
        for(Index_type j = j_start;j < j_end;++ j){
          for(Index_type k = k_start;k < k_end;++ k){
            body(i, j, k);
      } } } 
    }
};


#endif // _OPENMP


/******************************************************************
 *  forall3_permute(): Permutation function overloads
 ******************************************************************/

template<typename POLICY, typename PolicyI, typename PolicyJ, typename PolicyK, typename TI, typename TJ, typename TK, typename BODY>
RAJA_INLINE void forall3_permute(PERM_IJK, TI const &is_i, TJ const &is_j, TK const &is_k, BODY body){
  typedef typename POLICY::NextPolicy            NextPolicy;
  typedef typename POLICY::NextPolicy::PolicyTag NextPolicyTag;

  // Call next policy with permuted indices and policies
  forall3_policy<NextPolicy, PolicyI, PolicyJ, PolicyK>(NextPolicyTag(), is_i, is_j, is_k,
    [=](Index_type i, Index_type j, Index_type k){
      // Call body with non-permuted indices
      body(i, j, k);
    });
}

template<typename POLICY, typename PolicyI, typename PolicyJ, typename PolicyK, typename TI, typename TJ, typename TK, typename BODY>
RAJA_INLINE void forall3_permute(PERM_IKJ, TI const &is_i, TJ const &is_j, TK const &is_k, BODY body){
  typedef typename POLICY::NextPolicy            NextPolicy;
  typedef typename POLICY::NextPolicy::PolicyTag NextPolicyTag;

  // Call next policy with permuted indices and policies
  forall3_policy<NextPolicy, PolicyI, PolicyK, PolicyJ>(NextPolicyTag(), is_i, is_k, is_j,
    [=](Index_type i, Index_type k, Index_type j){
      // Call body with non-permuted indices
      body(i, j, k);
    });
}

template<typename POLICY, typename PolicyI, typename PolicyJ, typename PolicyK, typename TI, typename TJ, typename TK, typename BODY>
RAJA_INLINE void forall3_permute(PERM_JIK, TI const &is_i, TJ const &is_j, TK const &is_k, BODY body){
  typedef typename POLICY::NextPolicy            NextPolicy;
  typedef typename POLICY::NextPolicy::PolicyTag NextPolicyTag;

  // Call next policy with permuted indices and policies
  forall3_policy<NextPolicy, PolicyJ, PolicyI, PolicyK>(NextPolicyTag(), is_j, is_i, is_k,
    [=](Index_type j, Index_type i, Index_type k){
      // Call body with non-permuted indices
      body(i, j, k);
    });
}

template<typename POLICY, typename PolicyI, typename PolicyJ, typename PolicyK, typename TI, typename TJ, typename TK, typename BODY>
RAJA_INLINE void forall3_permute(PERM_JKI, TI const &is_i, TJ const &is_j, TK const &is_k, BODY body){
  typedef typename POLICY::NextPolicy            NextPolicy;
  typedef typename POLICY::NextPolicy::PolicyTag NextPolicyTag;

  // Call next policy with permuted indices and policies
  forall3_policy<NextPolicy, PolicyJ, PolicyK, PolicyI>(NextPolicyTag(), is_j, is_k, is_i,
    [=](Index_type j, Index_type k, Index_type i){
      // Call body with non-permuted indices
      body(i, j, k);
    });
}

template<typename POLICY, typename PolicyI, typename PolicyJ, typename PolicyK, typename TI, typename TJ, typename TK, typename BODY>
RAJA_INLINE void forall3_permute(PERM_KIJ, TI const &is_i, TJ const &is_j, TK const &is_k, BODY body){
  typedef typename POLICY::NextPolicy            NextPolicy;
  typedef typename POLICY::NextPolicy::PolicyTag NextPolicyTag;

  // Call next policy with permuted indices and policies
  forall3_policy<NextPolicy, PolicyK, PolicyI, PolicyJ>(NextPolicyTag(), is_k, is_i, is_j,
    [=](Index_type k, Index_type i, Index_type j){
      // Call body with non-permuted indices
      body(i, j, k);
    });
}

template<typename POLICY, typename PolicyI, typename PolicyJ, typename PolicyK, typename TI, typename TJ, typename TK, typename BODY>
RAJA_INLINE void forall3_permute(PERM_KJI, TI const &is_i, TJ const &is_j, TK const &is_k, BODY body){
  typedef typename POLICY::NextPolicy            NextPolicy;
  typedef typename POLICY::NextPolicy::PolicyTag NextPolicyTag;

  // Call next policy with permuted indices and policies
  forall3_policy<NextPolicy, PolicyK, PolicyJ, PolicyI>(NextPolicyTag(), is_k, is_j, is_i,
    [=](Index_type k, Index_type j, Index_type i){
      // Call body with non-permuted indices
      body(i, j, k);
    });
}


/******************************************************************
 *  forall3_policy() Policy Layer, specializations for policy tags
 ******************************************************************/


/*!
 * \brief Execute inner loops policy function.
 *
 * This is the default termination case.
 */
    template<typename POLICY, typename PolicyI, typename PolicyJ, typename PolicyK, typename TI, typename TJ, typename TK, typename BODY>
RAJA_INLINE void forall3_policy(Forall3_Execute_Tag, TI const &is_i, TJ const &is_j, TK const &is_k, BODY body){

  // Create executor object to launch loops
  Forall3Executor<PolicyI, PolicyJ, PolicyK, TI, TJ, TK> exec;

  // Launch loop body
  exec(is_i, is_j, is_k, body);
}


/*!
 * \brief Permutation policy function, providing loop interchange.
 */
    template<typename POLICY, typename PolicyI, typename PolicyJ, typename PolicyK, typename TI, typename TJ, typename TK, typename BODY>
RAJA_INLINE void forall3_policy(Forall3_Permute_Tag, TI const &is_i, TJ const &is_j, TK const &is_k, BODY body){
  // Get the loop permutation
  typedef typename POLICY::LoopOrder LoopOrder;

  // Call loop interchange overload to re-wrire indicies and policies
  forall3_permute<POLICY, PolicyI, PolicyJ, PolicyK>(LoopOrder(), is_i, is_j, is_k, body);
}


/*!
 * \brief OpenMP Parallel Region Section policy function.
 */
    template<typename POLICY, typename PolicyI, typename PolicyJ, typename PolicyK, typename TI, typename TJ, typename TK, typename BODY>
RAJA_INLINE void forall3_policy(Forall3_OMP_Parallel_Tag, TI const &is_i, TJ const &is_j, TK const &is_k, BODY body){
  typedef typename POLICY::NextPolicy            NextPolicy;
  typedef typename POLICY::NextPolicy::PolicyTag NextPolicyTag;

  // create OpenMP Parallel Region
#ifdef _OPENMP
#pragma omp parallel
#endif
  {
    // execute the next policy
    forall3_policy<NextPolicy, PolicyI, PolicyJ, PolicyK>(NextPolicyTag(), is_i, is_j, is_k, body);
  }
}


/*!
 * \brief Tiling policy function.
 */
    template<typename POLICY, typename PolicyI, typename PolicyJ, typename PolicyK, typename TI, typename TJ, typename TK, typename BODY>
RAJA_INLINE void forall3_policy(Forall3_Tile_Tag, TI const &is_i, TJ const &is_j, TK const &is_k, BODY body){
  typedef typename POLICY::NextPolicy            NextPolicy;
  typedef typename POLICY::NextPolicy::PolicyTag NextPolicyTag;
  typedef typename POLICY::TileI TileI;
  typedef typename POLICY::TileJ TileJ;
  typedef typename POLICY::TileK TileK;

  // execute the next policy
      forall_tile(TileI(), is_i, [=](RAJA::RangeSegment is_ii){
        forall_tile(TileJ(), is_j, [=](RAJA::RangeSegment is_jj){
          forall_tile(TileK(), is_k, [=](RAJA::RangeSegment is_kk){
        forall3_policy<NextPolicy, PolicyI, PolicyJ, PolicyK>(NextPolicyTag(), is_ii, is_jj, is_kk, body);
          });
        });
      });
}



/******************************************************************
 *  forall3 User API
 ******************************************************************/

/*!
 * \brief Provides abstraction of a 3-nested loop
 *
 * Provides index typing, and initial nested policy unwrapping
 */

template<typename POLICY, typename IdxI=Index_type, typename IdxJ=Index_type, typename IdxK=Index_type, typename TI, typename TJ, typename TK, typename BODY>
RAJA_INLINE void forall3(TI const &is_i, TJ const &is_j, TK const &is_k, BODY body){
  // extract next policy
  typedef typename POLICY::NextPolicy             NextPolicy;
  typedef typename POLICY::NextPolicy::PolicyTag  NextPolicyTag;

  // extract each loop's execution policy
  typedef typename POLICY::PolicyI                PolicyI;
  typedef typename POLICY::PolicyJ                PolicyJ;
  typedef typename POLICY::PolicyK                PolicyK;

  // call 'policy' layer with next policy
  forall3_policy<NextPolicy, PolicyI, PolicyJ, PolicyK>(NextPolicyTag(), is_i, is_j, is_k, 
    [=](Index_type i, Index_type j, Index_type k){
      body(IdxI(i), IdxJ(j), IdxK(k));
    }
  );
}



} // namespace RAJA
  
#endif

