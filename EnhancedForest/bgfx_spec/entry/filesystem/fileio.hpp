//
//  fileio.hpp
//  EnhancedForest
//
//  Created by Admin on 06.08.2021.
//

#pragma once

namespace bx {

struct FileReaderI;
struct FileWriterI;
struct AllocatorI;

} // namespace bx

namespace entry {

void fileIoInit();
void fileIoDeinit();

bx::FileReaderI *getFileReader();
bx::FileWriterI *getFileWriter();

static bx::FilePath s_currentDir;

void setCurrentDir(const char *_dir);

} // namespace entry
