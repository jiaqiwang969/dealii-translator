//include/deal.II-translator/lac/read_write_vector_0.txt
// ---------------------------------------------------------------------
//
// Copyright (C) 2015 - 2021 by the deal.II authors
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

#ifndef dealii_read_write_vector_h
#define dealii_read_write_vector_h

#include <deal.II/base/config.h>

#include <deal.II/base/communication_pattern_base.h>
#include <deal.II/base/index_set.h>
#include <deal.II/base/memory_consumption.h>
#include <deal.II/base/mpi.h>
#include <deal.II/base/parallel.h>
#include <deal.II/base/subscriptor.h>
#include <deal.II/base/template_constraints.h>
#include <deal.II/base/types.h>
#include <deal.II/base/utilities.h>

#include <deal.II/lac/vector_operation.h>

#include <cstdlib>
#include <cstring>
#include <iomanip>

#ifdef DEAL_II_WITH_TRILINOS
#  include <deal.II/lac/trilinos_epetra_communication_pattern.h>
#  include <deal.II/lac/trilinos_epetra_vector.h>
#  include <deal.II/lac/trilinos_tpetra_vector.h>

#  include <Epetra_MultiVector.h>

#endif

DEAL_II_NAMESPACE_OPEN

// Forward declarations
#ifndef DOXYGEN
namespace LinearAlgebra
{
  template <typename>
  class Vector;
  namespace distributed
  {
    template <typename, typename>
    class Vector;
  } // namespace distributed
} // namespace LinearAlgebra

#  ifdef DEAL_II_WITH_PETSC
namespace PETScWrappers
{
  namespace MPI
  {
    class Vector;
  }
} // namespace PETScWrappers
#  endif

#  ifdef DEAL_II_WITH_TRILINOS
namespace TrilinosWrappers
{
  namespace MPI
  {
    class Vector;
  }
} // namespace TrilinosWrappers
#  endif

#  ifdef DEAL_II_WITH_CUDA
namespace LinearAlgebra
{
  namespace CUDAWrappers
  {
    template <typename>
    class Vector;
  }
} // namespace LinearAlgebra
#  endif
#endif

namespace LinearAlgebra
{
  /*!   @addtogroup Vectors  
     * @{   
*
*/

  /**
   * ReadWriteVector???????????? ${\mathbb R}^N$
   * ????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
   * $N$
   * ??????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
   * ?????????????????????????????????????????????
   * ?????????????????????????????????????????????????????????
   * ReadWriteVector?????????????????????VectorSpaceVector?????????????????????????????????
   * TrilinosWrappers::MPI::Vector ??? PETScWrappers::MPI::Vector. <h3>Storing
   * elements</h3>?????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????operator()()???operator[]()???????????????????????????global_to_local()???<i>global</i>??????????????????<i>local</i>?????????????????????????????????????????????????????????????????????????????????????????????????????????
   * ??????????????????????????????????????????????????????????????????????????????????????????????????????????????????<i>global</i>????????????????????????????????????????????????????????????????????????????????????????????????local_element()??????????????????????????????????????????????????????<i>in
   * which
   * order</i>??????????????????????????????????????????????????????????????????????????????????????????????????????????????????
   * ??????????????? IndexSet::largest_range_starting_index()
   * ??????????????????????????????????????????
   *
   */
  template <typename Number>
  class ReadWriteVector : public Subscriptor
  {
  public:
    /**
     * ????????????????????????????????????????????????????????????<tt>C++</tt>???????????????<tt>vector<...></tt>????????????????????????
     *
     */
    using value_type      = Number;
    using pointer         = value_type *;
    using const_pointer   = const value_type *;
    using iterator        = value_type *;
    using const_iterator  = const value_type *;
    using reference       = value_type &;
    using const_reference = const value_type &;
    using size_type       = types::global_dof_index;
    using real_type       = typename numbers::NumberTraits<Number>::real_type;

    /**
     * @name  1: ??????????????????
     *
     */
    //@{
    /**
     * ?????????????????????
     *
     */
    ReadWriteVector();

    /**
     * ?????????????????????
     *
     */
    ReadWriteVector(const ReadWriteVector<Number> &in_vector);

    /**
     * ???????????????????????????????????????????????????????????????[0,size]???
     *
     */
    explicit ReadWriteVector(const size_type size);

    /**
     * ????????????????????????????????????????????????IndexSet @p
     * locally_stored_indices. ?????????
     *
     */
    explicit ReadWriteVector(const IndexSet &locally_stored_indices);

    /**
     * ????????????
     *
     */
    ~ReadWriteVector() override = default;

    /**
     * ????????????????????????????????? @p size.
     * ????????????????????????[0,size]???        ???????????? @p
     * omit_zeroing_entries
     * ????????????false???????????????????????????0??????????????????????????????????????????????????????????????????????????????????????????????????????
     *
     */
    virtual void
    reinit(const size_type size, const bool omit_zeroing_entries = false);

    /**
     * ????????????????????? @p in_vector
     * ?????????IndexSet?????????????????????????????????        ????????????
     * @p omit_zeroing_entries
     * ????????????false???????????????????????????0????????????????????????????????????????????????????????????????????????????????????????????????
     *
     */
    template <typename Number2>
    void
    reinit(const ReadWriteVector<Number2> &in_vector,
           const bool                      omit_zeroing_entries = false);

    /**
     * ??????????????????????????? @p  locally_stored_indices?????????
     * ???????????? @p omit_zeroing_entries
     * ????????????false???????????????????????????0????????????????????????????????????????????????????????????????????????????????????????????????
     * local_stored_indices???
     *
     */
    virtual void
    reinit(const IndexSet &locally_stored_indices,
           const bool      omit_zeroing_entries = false);


#ifdef DEAL_II_WITH_TRILINOS
#  ifdef DEAL_II_WITH_MPI
    /**
     * ????????????????????????ghosted???non-ghosted???????????????????????????????????????????????????????????????????????????
     * @note
     * ?????????????????????????????????????????????ReadWriteVector???????????????????????????????????????
     * @p trilinos_vec.
     * ???????????????????????????????????????????????????????????????????????????
     * TrilinosWrappers::MPI::Vector ??????????????????
     *
     */
    void
    reinit(const TrilinosWrappers::MPI::Vector &trilinos_vec);
#  endif
#endif

    /**
     * ???????????????????????????????????? @p func
     * ?????????????????????????????????
     * @code
     * struct Functor
     * {
     * void operator() (Number &value);
     * };
     * @endcode
     * @note
     * ?????????????????????????????????read_write_vector.templates.h???
     *
     */
    template <typename Functor>
    void
    apply(const Functor &func);

    /**
     * ?????????????????????????????????????????????  @p v.
     * ???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
     * ???????????????????????????C++??????????????? @p swap
     * ??????????????????????????????????????????<tt>swap(u,v)</tt>?????????????????????<tt>u.swap(v)</tt>????????????????????????????????????
     *
     */
    void
    swap(ReadWriteVector<Number> &v);

    /**
     * ??????????????????????????????IndexSet  @p in_vector.  ???
     *
     */
    ReadWriteVector<Number> &
    operator=(const ReadWriteVector<Number> &in_vector);

    /**
     * ??????????????????????????????IndexSet  @p in_vector.  ???
     *
     */
    template <typename Number2>
    ReadWriteVector<Number> &
    operator=(const ReadWriteVector<Number2> &in_vector);

    /**
     * ???????????????????????????????????????  @p s.  ????????? @p s
     * ??????????????????????????????????????????
     *
     */
    ReadWriteVector<Number> &
    operator=(const Number s);

    /**
     * ??????????????? @p vec.   VectorOperation::values   @p operation
     * ??????????????????IndexSet??????????????????????????????????????? @p V
     * ?????????????????????????????????????????????????????????????????????????????????
     * @note  ?????? @p communication_pattern
     * ??????????????????????????????????????????????????????????????????
     *
     */
    void
    import(const dealii::Vector<Number> &vec,
           VectorOperation::values       operation,
           const std::shared_ptr<const Utilities::MPI::CommunicationPatternBase>
             &communication_pattern = {});

    /**
     * ??????????????? @p vec.   VectorOperation::values   @p operation
     * ??????????????????IndexSet??????????????????????????????????????? @p V
     * ?????????????????????????????????????????????????????????????????????????????????
     * @note ?????? @p communication_pattern
     * ??????????????????????????????????????????????????????????????????
     *
     */
    void
    import(const LinearAlgebra::Vector<Number> &vec,
           VectorOperation::values              operation,
           const std::shared_ptr<const Utilities::MPI::CommunicationPatternBase>
             &communication_pattern = {});

    /**
     * ??????????????? @p vec.  VectorOperation::values  @p operation
     * ??????????????????IndexSet??????????????????????????????????????? @p V
     * ???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
     *
     */
    template <typename MemorySpace>
    void
    import(const distributed::Vector<Number, MemorySpace> &vec,
           VectorOperation::values                         operation,
           const std::shared_ptr<const Utilities::MPI::CommunicationPatternBase>
             &communication_pattern = {});

#ifdef DEAL_II_WITH_PETSC
    /**
     * ??????????????? @p petsc_vec.  VectorOperation::values  @p operation
     * ??????????????????IndexSet??????????????????????????????????????? @p V
     * ??????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
     *
     */
    void
    import(const PETScWrappers::MPI::Vector &petsc_vec,
           VectorOperation::values           operation,
           const std::shared_ptr<const Utilities::MPI::CommunicationPatternBase>
             &communication_pattern = {});
#endif

#ifdef DEAL_II_WITH_TRILINOS
    /**
     * ??????????????? @p trilinos_vec.  VectorOperation::values  @p operation
     * ??????????????????IndexSet??????????????????????????????????????? @p V
     * ???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
     * @note  @p trilinos_vec ???????????????????????????
     *
     */
    void
    import(const TrilinosWrappers::MPI::Vector &trilinos_vec,
           VectorOperation::values              operation,
           const std::shared_ptr<const Utilities::MPI::CommunicationPatternBase>
             &communication_pattern = {});

#  ifdef DEAL_II_WITH_MPI
#    ifdef DEAL_II_TRILINOS_WITH_TPETRA
    /**
     * ??????????????? @p tpetra_vec.  VectorOperation::values  @p operation
     * ??????????????????IndexSet??????????????????????????????????????? @p V
     * ???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
     *
     */
    void
    import(const TpetraWrappers::Vector<Number> &tpetra_vec,
           VectorOperation::values               operation,
           const std::shared_ptr<const Utilities::MPI::CommunicationPatternBase>
             &communication_pattern = {});
#    endif

    /**
     * ??????????????? @p epetra_vec.  VectorOperation::values  @p operation
     * ??????????????????IndexSet??????????????????????????????????????? @p V
     * ???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
     *
     */
    void
    import(const EpetraWrappers::Vector &epetra_vec,
           VectorOperation::values       operation,
           const std::shared_ptr<const Utilities::MPI::CommunicationPatternBase>
             &communication_pattern = {});
#  endif
#endif

#ifdef DEAL_II_WITH_CUDA
    /**
     * ??????????????? @p cuda_vec.  VectorOperation::values  @p operation
     * ??????????????????IndexSet??????????????????????????????????????? @p V
     * ???????????????????????????????????????????????????????????????????????????????????????????????????????????????
     *
     */
    void
    import(const CUDAWrappers::Vector<Number> &cuda_vec,
           VectorOperation::values             operation,
           const std::shared_ptr<const Utilities::MPI::CommunicationPatternBase>
             &communication_pattern = {});
#endif

    /**
     * ???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????n_elements()????????????????????????????????????????????????????????????
     *
     */
    size_type
    size() const;

    /**
     * ???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????size()????????????
     * @deprecated  ??????local_owned_size()?????????
     *
     */
    DEAL_II_DEPRECATED
    size_type
    n_elements() const;

    /**
     * ????????????????????????????????????????????????????????????
     *
     */
    size_type
    locally_owned_size() const;

    /**
     * ??????IndexSet????????????????????????????????????
     *
     */
    const IndexSet &
    get_stored_elements() const;

    /**
     * ??? @p ReadWriteVector
     * ????????????C++????????????<tt>vector<>/tt>????????????????????????<i>locally
     * stored</i>???????????????????????????????????????
     *
     */
    iterator
    begin();

    /**
     * ???????????????????????????????????????????????????????????????
     *
     */
    const_iterator
    begin() const;

    /**
     * ??????????????????????????????????????????????????????????????????????????????
     *
     */
    iterator
    end();

    /**
     * ???????????????????????????????????????????????????????????????????????????????????????
     *
     */
    const_iterator
    end() const;
    //@}


    /**
     * @name  2: ????????????
     *
     */
    //@{

    /**
     * ??????????????? @p  global_index???????????????????????? @p
     * global_index
     * ????????????????????????????????????????????????????????????
     *
     */
    Number
    operator()(const size_type global_index) const;

    /**
     * ??? @p  global_index???????????????????????????????????????????????? @p
     * global_index ?????????????????????????????????????????????????????????
     *
     */
    Number &
    operator()(const size_type global_index);

    /**
     * ??????????????? @p  global_index???????????????????????? @p
     * global_index ?????????????????????????????????????????????????????????
     * ???????????????operator()??????????????????
     *
     */
    Number operator[](const size_type global_index) const;

    /**
     * ???????????????????????? @p global_index???????????????????????? @p
     * global_index
     * ????????????????????????????????????????????????????????????
     * ???????????????operator()??????????????????
     *
     */
    Number &operator[](const size_type global_index);

    /**
     * ?????????operator()??????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
     * ?????????????????????????????? @p v,
     * ???????????????????????????????????????
     * @code
     * for (unsigned int i=0; i<indices.size(); ++i)
     *   values[i] = v[indices[i]];
     * @endcode
     * @pre  @p indices ??? @p values ????????????????????????????????????
     *
     */
    template <typename Number2>
    void
    extract_subvector_to(const std::vector<size_type> &indices,
                         std::vector<Number2> &        values) const;

    /**
     * ????????????????????????operator()??????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
     * ?????????????????????????????? @p v,
     * ???????????????????????????????????????
     * @code
     * ForwardIterator indices_p = indices_begin;
     * OutputIterator  values_p  = values_begin;
     * while (indices_p != indices_end)
     * {
     *  values_p = v[*indices_p];
     *   ++indices_p;
     *   ++values_p;
     * }
     * @endcode
     * @pre  ????????????????????? @p values_begin
     * ???????????????????????????????????????????????? @p indices_begin ???
     * @p indices_end. ?????????????????????
     *
     */
    template <typename ForwardIterator, typename OutputIterator>
    void
    extract_subvector_to(ForwardIterator       indices_begin,
                         const ForwardIterator indices_end,
                         OutputIterator        values_begin) const;

    /**
     * ???????????? @p local_index. ?????????????????????
     * ?????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
     * ??????????????????????????????????????????
     *
     */
    Number
    local_element(const size_type local_index) const;

    /**
     * ??? @p local_index. ?????????????????????????????????
     * ????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
     * ??????????????????????????????????????????
     *
     */
    Number &
    local_element(const size_type local_index);
    //@}


    /**
     * @name  3: ????????????
     *
     */
    //@{

    /**
     * ????????????????????? @p values ???????????????????????? @p indices.
     * ???????????????????????????
     *
     */
    template <typename Number2>
    void
    add(const std::vector<size_type> &indices,
        const std::vector<Number2> &  values);

    /**
     * ???????????????????????????????????????????????????????????????????????????
     *
     */
    template <typename Number2>
    void
    add(const std::vector<size_type> &  indices,
        const ReadWriteVector<Number2> &values);

    /**
     * ?????????<tt>n_elements</tt>??????????????????????????????????????????????????????????????????????????????<tt>add()</tt>??????????????????????????????
     *
     */
    template <typename Number2>
    void
    add(const size_type  n_elements,
        const size_type *indices,
        const Number2 *  values);

    /**
     * ??????????????????????????????  @p out.  ???
     *
     */
    void
    print(std::ostream &     out,
          const unsigned int precision  = 3,
          const bool         scientific = true) const;

    /**
     * ???????????????????????????????????????????????????
     *
     */
    std::size_t
    memory_consumption() const;
    //@}

  protected:
#ifdef DEAL_II_WITH_TRILINOS
#  ifdef DEAL_II_TRILINOS_WITH_TPETRA
    /**
     * ?????????????????????????????????????????????IndexSet????????????  @p
     * tpetra_vector.  ??????????????????????????????????????????????????????
     *
     */
    void
    import(
      const Tpetra::Vector<Number, int, types::global_dof_index> &tpetra_vector,
      const IndexSet &        locally_owned_elements,
      VectorOperation::values operation,
      const MPI_Comm &        mpi_comm,
      const std::shared_ptr<const Utilities::MPI::CommunicationPatternBase>
        &communication_pattern);
#  endif

    /**
     * ??????????????????????????????IndexSet??????????????????  @p
     * multivector.  ???????????????????????????????????????????????????
     *
     */
    void
    import(const Epetra_MultiVector &multivector,
           const IndexSet &          locally_owned_elements,
           VectorOperation::values   operation,
           const MPI_Comm &          mpi_comm,
           const std::shared_ptr<const Utilities::MPI::CommunicationPatternBase>
             &communication_pattern);
#endif

    /**
     * ?????? @p global_index. ??????????????????
     *
     */
    unsigned int
    global_to_local(const types::global_dof_index global_index) const
    {
      // the following will throw an exception if the global_index is not
      // in the remaining_elements
      return static_cast<unsigned int>(
        stored_elements.index_within_set(global_index));
    }

    /**
     * ?????????????????????????????????val??????????????????
     *
     */
    void
    resize_val(const size_type new_allocated_size);

#if defined(DEAL_II_WITH_TRILINOS) && defined(DEAL_II_WITH_MPI)
#  ifdef DEAL_II_TRILINOS_WITH_TPETRA
    /**
     * ???????????? TpetraWrappers::CommunicationPattern
     * ??????????????????????????????????????????
     *
     */
    TpetraWrappers::CommunicationPattern
    create_tpetra_comm_pattern(const IndexSet &source_index_set,
                               const MPI_Comm &mpi_comm);
#  endif

    /**
     * ???????????? EpetraWrappers::CommunicationPattern
     * ????????????????????????????????????
     *
     */
    EpetraWrappers::CommunicationPattern
    create_epetra_comm_pattern(const IndexSet &source_index_set,
                               const MPI_Comm &mpi_comm);
#endif

    /**
     * ???????????????????????????
     *
     */
    IndexSet stored_elements;

    /**
     * ?????????????????????????????????????????????
     *
     */
    IndexSet source_stored_elements;

    /**
     * Source_stored_elements IndexSet???????????????????????????????????????
     *
     */
    std::shared_ptr<Utilities::MPI::CommunicationPatternBase> comm_pattern;

    /**
     * ???????????????????????????????????????????????????
     *
     */
    std::unique_ptr<Number[], decltype(std::free) *> values;

    /**
     * ????????????TBB?????????????????????????????????????????????????????????????????????
     *
     */
    mutable std::shared_ptr<::dealii::parallel::internal::TBBPartitioner>
      thread_loop_partitioner;

    // Make all other ReadWriteVector types friends.
    template <typename Number2>
    friend class ReadWriteVector;

  private:
    /**
     * ??????????????????????????????Functor??????????????????????????????????????????????????????????????????
     * tbb::parallel_for ????????????????????????????????????TBBForFunctor???
     *
     */
    template <typename Functor>
    class FunctorTemplate
    {
    public:
      /**
       * ???????????????????????????????????????????????????
       *
       */
      FunctorTemplate(ReadWriteVector<Number> &parent, const Functor &functor);

      /**
       * ????????????functor???????????????????????????
       *
       */
      virtual void
      operator()(const size_type begin, const size_type end);

    private:
      /**
       * ?????????FunctorTemplate???ReadWriteVector??????????????????
       *
       */
      ReadWriteVector &parent;

      /**
       * ??????????????????
       *
       */
      const Functor &functor;
    };
  };

   /*@}*/ 


   /*---------------------------- Inline functions ---------------------------*/ 

#ifndef DOXYGEN

  template <typename Number>
  inline ReadWriteVector<Number>::ReadWriteVector()
    : Subscriptor()
    , values(nullptr, free)
  {
    // virtual functions called in constructors and destructors never use the
    // override in a derived class
    // for clarity be explicit on which function is called
    ReadWriteVector<Number>::reinit(0, true);
  }



  template <typename Number>
  inline ReadWriteVector<Number>::ReadWriteVector(
    const ReadWriteVector<Number> &v)
    : Subscriptor()
    , values(nullptr, free)
  {
    this->operator=(v);
  }



  template <typename Number>
  inline ReadWriteVector<Number>::ReadWriteVector(const size_type size)
    : Subscriptor()
    , values(nullptr, free)
  {
    // virtual functions called in constructors and destructors never use the
    // override in a derived class
    // for clarity be explicit on which function is called
    ReadWriteVector<Number>::reinit(size, false);
  }



  template <typename Number>
  inline ReadWriteVector<Number>::ReadWriteVector(
    const IndexSet &locally_stored_indices)
    : Subscriptor()
    , values(nullptr, free)
  {
    // virtual functions called in constructors and destructors never use the
    // override in a derived class
    // for clarity be explicit on which function is called
    ReadWriteVector<Number>::reinit(locally_stored_indices);
  }



  template <typename Number>
  inline typename ReadWriteVector<Number>::size_type
  ReadWriteVector<Number>::size() const
  {
    return stored_elements.size();
  }



  template <typename Number>
  inline typename ReadWriteVector<Number>::size_type
  ReadWriteVector<Number>::n_elements() const
  {
    return stored_elements.n_elements();
  }



  template <typename Number>
  inline typename ReadWriteVector<Number>::size_type
  ReadWriteVector<Number>::locally_owned_size() const
  {
    return stored_elements.n_elements();
  }



  template <typename Number>
  inline const IndexSet &
  ReadWriteVector<Number>::get_stored_elements() const
  {
    return stored_elements;
  }



  template <typename Number>
  inline typename ReadWriteVector<Number>::iterator
  ReadWriteVector<Number>::begin()
  {
    return values.get();
  }



  template <typename Number>
  inline typename ReadWriteVector<Number>::const_iterator
  ReadWriteVector<Number>::begin() const
  {
    return values.get();
  }



  template <typename Number>
  inline typename ReadWriteVector<Number>::iterator
  ReadWriteVector<Number>::end()
  {
    return values.get() + this->n_elements();
  }



  template <typename Number>
  inline typename ReadWriteVector<Number>::const_iterator
  ReadWriteVector<Number>::end() const
  {
    return values.get() + this->n_elements();
  }



  template <typename Number>
  inline Number
  ReadWriteVector<Number>::operator()(const size_type global_index) const
  {
    return values[global_to_local(global_index)];
  }



  template <typename Number>
  inline Number &
  ReadWriteVector<Number>::operator()(const size_type global_index)
  {
    return values[global_to_local(global_index)];
  }



  template <typename Number>
  inline Number ReadWriteVector<Number>::
                operator[](const size_type global_index) const
  {
    return operator()(global_index);
  }



  template <typename Number>
  inline Number &ReadWriteVector<Number>::
                 operator[](const size_type global_index)
  {
    return operator()(global_index);
  }



  template <typename Number>
  template <typename Number2>
  inline void
  ReadWriteVector<Number>::extract_subvector_to(
    const std::vector<size_type> &indices,
    std::vector<Number2> &        extracted_values) const
  {
    for (size_type i = 0; i < indices.size(); ++i)
      extracted_values[i] = operator()(indices[i]);
  }



  template <typename Number>
  template <typename ForwardIterator, typename OutputIterator>
  inline void
  ReadWriteVector<Number>::extract_subvector_to(
    ForwardIterator       indices_begin,
    const ForwardIterator indices_end,
    OutputIterator        values_begin) const
  {
    while (indices_begin != indices_end)
      {
        *values_begin = operator()(*indices_begin);
        indices_begin++;
        values_begin++;
      }
  }



  template <typename Number>
  inline Number
  ReadWriteVector<Number>::local_element(const size_type local_index) const
  {
    AssertIndexRange(local_index, this->n_elements());

    return values[local_index];
  }



  template <typename Number>
  inline Number &
  ReadWriteVector<Number>::local_element(const size_type local_index)
  {
    AssertIndexRange(local_index, this->n_elements());

    return values[local_index];
  }



  template <typename Number>
  template <typename Number2>
  inline void
  ReadWriteVector<Number>::add(const std::vector<size_type> &indices,
                               const std::vector<Number2> &  values)
  {
    AssertDimension(indices.size(), values.size());
    add(indices.size(), indices.data(), values.data());
  }



  template <typename Number>
  template <typename Number2>
  inline void
  ReadWriteVector<Number>::add(const std::vector<size_type> &  indices,
                               const ReadWriteVector<Number2> &values)
  {
    const size_type size = indices.size();
    for (size_type i = 0; i < size; ++i)
      {
        Assert(
          numbers::is_finite(values[i]),
          ExcMessage(
            "The given value is not finite but either infinite or Not A Number (NaN)"));
        this->operator()(indices[i]) += values[indices[i]];
      }
  }



  template <typename Number>
  template <typename Number2>
  inline void
  ReadWriteVector<Number>::add(const size_type  n_indices,
                               const size_type *indices,
                               const Number2 *  values_to_add)
  {
    for (size_type i = 0; i < n_indices; ++i)
      {
        Assert(
          numbers::is_finite(values[i]),
          ExcMessage(
            "The given value is not finite but either infinite or Not A Number (NaN)"));
        this->operator()(indices[i]) += values_to_add[i];
      }
  }



  template <typename Number>
  template <typename Functor>
  inline ReadWriteVector<Number>::FunctorTemplate<Functor>::FunctorTemplate(
    ReadWriteVector<Number> &parent,
    const Functor &          functor)
    : parent(parent)
    , functor(functor)
  {}



  template <typename Number>
  template <typename Functor>
  void
  ReadWriteVector<Number>::FunctorTemplate<Functor>::
  operator()(const size_type begin, const size_type end)
  {
    for (size_type i = begin; i < end; ++i)
      functor(parent.values[i]);
  }

#endif // ifndef DOXYGEN

} // end of namespace LinearAlgebra



/**
 * ???????????? @p swap
 * ???????????????C++????????????????????????????????????????????????????????????????????????????????????????????????????????????
 * @relatesalso  Vectors
 *
 *
 */
template <typename Number>
inline void
swap(LinearAlgebra::ReadWriteVector<Number> &u,
     LinearAlgebra::ReadWriteVector<Number> &v)
{
  u.swap(v);
}


DEAL_II_NAMESPACE_CLOSE

#endif


