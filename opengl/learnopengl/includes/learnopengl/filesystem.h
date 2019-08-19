#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <cstdlib>
#include "root_directory.h"

class FileSystem
{
public:
    static std::string getPath(const std::string &path)
    {
        if (getRoot() != "") {
            return FileSystem::getPathRelativeRoot(path);
        } else {
            return FileSystem::getPathRelativeBinary(path);
        }
    }

private:
    static std::string const &getRoot()
    {
        static char const *envRoot = getenv("LOGL_ROOT_PATH");
        static char const *givenRoot = (envRoot != nullptr ? envRoot : logl_root); 
        static std::string root = (givenRoot != nullptr ? givenRoot : "");
        return root;
    }

    static std::string getPathRelativeRoot(const std::string &path)
    {
        return getRoot() + std::string("/") + path;
    }

    static std::string getPathRelativeBinary(const std::string &path)
    {
        return "../../../" + path;
    }
};

#endif /* FILESYSTEM_H */
