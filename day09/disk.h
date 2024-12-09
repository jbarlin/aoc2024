#pragma once

#include <vector>
#include "contents.h"
#include <optional>
#include <iostream>

namespace day09 {
    class Disk {
        public:
            const std::vector<Free> frees;
            const std::vector<File> files;
            Disk(const std::vector<Free> &free, const std::vector<File> &files): frees{free},files{files}{};
            const Disk defragment() const;
            const Disk defragment_contigous() const;
            const unsigned long long checksum() const;
    };
}