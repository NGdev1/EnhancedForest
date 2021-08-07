//
//  fileio.cpp
//  EnhancedForest
//
//  Created by Admin on 06.08.2021.
//

#include <bx/bx.h>
#include <bx/file.h>
#include <bx/filepath.h>
#include <bx/string.h>

#include "bxallocator.hpp"
#include "fileio.hpp"

static bx::FileReaderI *s_fileReader = NULL;
static bx::FileWriterI *s_fileWriter = NULL;

namespace entry {

void setCurrentDir(const char *_dir) {
    s_currentDir.set(_dir);
}

class FileReader : public bx::FileReader {
    typedef bx::FileReader super;

public:
    virtual bool open(const bx::FilePath &_filePath, bx::Error *_err) override {
        bx::FilePath filePath(s_currentDir);
        filePath.join(_filePath);
        return super::open(filePath, _err);
    }
};

class FileWriter : public bx::FileWriter {
    typedef bx::FileWriter super;

public:
    virtual bool open(const bx::FilePath &_filePath, bool _append, bx::Error *_err) override {
        bx::FilePath filePath(s_currentDir);
        filePath.join(_filePath);
        return super::open(filePath, _append, _err);
    }
};

bx::FileReaderI *getFileReader() {
    return s_fileReader;
}

bx::FileWriterI *getFileWriter() {
    return s_fileWriter;
}

void fileIoInit() {
    s_fileReader = BX_NEW(getAllocator(), FileReader);
    s_fileWriter = BX_NEW(getAllocator(), FileWriter);
}

void fileIoDeinit() {
    BX_DELETE(getAllocator(), s_fileReader);
    s_fileReader = NULL;

    BX_DELETE(getAllocator(), s_fileWriter);
    s_fileWriter = NULL;
}

} // namespace entry
