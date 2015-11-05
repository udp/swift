#ifndef LLVM_SOURCEKITD_TEST_TESTOPTIONS_H
#define LLVM_SOURCEKITD_TEST_TESTOPTIONS_H

#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/Optional.h"
#include <string>

namespace sourcekitd_test {

enum class SourceKitRequest {
  None,
  Index,
  CodeComplete,
  CodeCompleteOpen,
  CodeCompleteClose,
  CodeCompleteUpdate,
  CodeCompleteCacheOnDisk,
  CodeCompleteSetPopularAPI,
  CursorInfo,
  RelatedIdents,
  SyntaxMap,
  Structure,
  Format,
  ExpandPlaceholder,
  DocInfo,
  SemanticInfo,
  InterfaceGen,
  InterfaceGenOpen,
  FindUSR,
  FindInterfaceDoc,
  Open,
  Edit,
  PrintAnnotations,
  PrintDiags,
  ExtractComment
};

struct TestOptions {
  SourceKitRequest Request = SourceKitRequest::None;
  std::string SourceFile;
  std::string TextInputFile;
  std::string JsonRequestPath;
  llvm::Optional<std::string> SourceText;
  unsigned Line = 0;
  unsigned Col = 0;
  unsigned Offset = 0;
  unsigned Length = 0;
  llvm::Optional<std::string> ReplaceText;
  std::string ModuleName;
  std::string HeaderPath;
  bool PassAsSourceText = false;
  std::string CachePath;
  llvm::SmallVector<std::string, 4> RequestOptions;
  llvm::ArrayRef<const char *> CompilerArgs;
  std::string USR;
  bool CheckInterfaceIsASCII = false;
  bool UsedSema = false;

  bool parseArgs(llvm::ArrayRef<const char *> Args);
};

}

#endif
