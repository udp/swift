//===--- LLVM.h - Import various common LLVM datatypes ----------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
/// \file
/// \brief Forward declares and imports various common LLVM datatypes that
/// clangd wants to use unqualified.
///
//===----------------------------------------------------------------------===//

#ifndef LLVM_SOURCEKIT_CORE_LLVM_H
#define LLVM_SOURCEKIT_CORE_LLVM_H

// Do not proliferate #includes here, require clients to #include their
// dependencies.
// Casting.h has complex templates that cannot be easily forward declared.
#include "llvm/Support/Casting.h"
// None.h includes an enumerator that is desired & cannot be forward declared
// without a definition of NoneType.
#include "llvm/ADT/None.h"
#include <memory>

namespace llvm {
  // ADT's.
  class StringRef;
  class Twine;
  template<typename T> class ArrayRef;
  template<unsigned InternalLen> class SmallString;
  template<typename T, unsigned N> class SmallVector;
  template<typename T> class SmallVectorImpl;
  template<typename T> class Optional;

  template<typename T>
  struct SaveAndRestore;

  // Reference counting.
  template <typename T> class IntrusiveRefCntPtr;
  template <typename T> struct IntrusiveRefCntPtrInfo;

  class raw_ostream;
  // TODO: DenseMap, ...

  template<class To, class From>
  struct cast_retty_impl<To, std::shared_ptr<From>> {
    typedef std::shared_ptr<To> ret_type;
  };

  template <typename To, typename From, typename Enabler>
  struct isa_impl<To, std::shared_ptr<From>, Enabler> {
    static inline bool doit(const std::shared_ptr<From> &Val) {
      return To::classof(Val.get());
    }
  };

  template<class To, class From>
  struct cast_convert_val<To, std::shared_ptr<From>, std::shared_ptr<From>> {
    static typename cast_retty<To, std::shared_ptr<From>>::ret_type doit(
        const std::shared_ptr<From> &Val) {
      return std::shared_ptr<To>(Val, static_cast<To*>(Val.get()));
    }
  };
}

namespace swift {
  template <class Derived> class ThreadSafeRefCountedBase;
  class ThreadSafeRefCountedBaseVPTR;
}

namespace SourceKit {
  // Casting operators.
  using llvm::isa;
  using llvm::cast;
  using llvm::dyn_cast;
  using llvm::dyn_cast_or_null;
  using llvm::cast_or_null;
  
  // ADT's.
  using llvm::StringRef;
  using llvm::Twine;
  using llvm::ArrayRef;
  using llvm::SmallString;
  using llvm::SmallVector;
  using llvm::SmallVectorImpl;
  using llvm::SaveAndRestore;
  using llvm::Optional;
  using llvm::None;

  // Reference counting.
  using llvm::IntrusiveRefCntPtr;
  using llvm::IntrusiveRefCntPtrInfo;
  using swift::ThreadSafeRefCountedBase;
  using swift::ThreadSafeRefCountedBaseVPTR;
  template <typename T> class ThreadSafeRefCntPtr;

  using llvm::raw_ostream;

  template <typename T>
  using RefPtr = IntrusiveRefCntPtr<T>;
  
} // end namespace SourceKit.

#endif
