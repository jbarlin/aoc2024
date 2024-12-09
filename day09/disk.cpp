#include "disk.h"

namespace day09
{

    const void print(const std::vector<File> &files)
    {
        std::cout << "\t";
        for (File f : files)
        {
            std::cout << " F@" << f.start_posn << "#" << f.size << "!" << f.id;
        }
        std::cout << "" << std::endl;
    }

    const void print(const std::vector<Free> &free)
    {
        std::cout << "\t";
        for (Free f : free)
        {
            std::cout << " B@" << f.start_posn << "#" << f.size;
        }
        std::cout << "" << std::endl;
    }

    const Disk Disk::defragment_contigous() const
    {
        std::vector<File> defragged;
        std::vector<Free> was_frees = frees;
        std::vector<File> was_files = files;
        while (was_files.size() > 0)
        {
            const File curr_file = was_files.back();
            // Because no matter what, it is gonna end up in the defragged pile!
            was_files.pop_back();

            bool found_home = false;

            for (long unsigned int i = 0; i < was_frees.size(); i++)
            {
                const Free curr_free = was_frees[i];
                if(curr_free.size >= curr_file.size && curr_free.start_posn < curr_file.start_posn){
                    // Ooh found a home!
                    found_home = true;
                    defragged.push_back(File(curr_free.start_posn, curr_file.size, curr_file.id));
                    ull free_after = curr_free.size - curr_file.size;
                    ull free_start_posn = curr_free.start_posn + curr_file.size;
                    was_frees[i] = Free(free_start_posn, free_after);
                    break;
                }
            }

            if (!found_home)
            {
                // No biggie, leave in place!~
                defragged.push_back(curr_file);
            }
        }
        return Disk(std::vector<Free>(), defragged);
    }

    const Disk Disk::defragment() const
    {
        std::vector<File> defragged;
        std::vector<Free> was_frees = frees;
        std::vector<File> was_files = files;
        while (was_frees.size() > 0)
        {
            if (was_files.empty())
            {
                // No more files! Woot!
                break;
            }
            Free curr_free = was_frees.front();
            File curr_file = was_files.back();
            // Check if our gap is beyond the file...
            if (curr_free.start_posn > curr_file.start_posn)
            {
                break;
            }
            was_files.pop_back();
            was_frees.erase(was_frees.begin());
            // Will we fit?
            if (curr_free.size == curr_file.size)
            {
                // We do! Perfectly!
                defragged.push_back(File(curr_free.start_posn, curr_file.size, curr_file.id));
            }
            else if (curr_free.size < curr_file.size)
            {
                // We don't quite fit... Push in what we can fit, and then push in the rest
                defragged.push_back(File(curr_free.start_posn, curr_free.size, curr_file.id));
                was_files.push_back(File(curr_file.start_posn, curr_file.size - curr_free.size, curr_file.id));
            }
            else
            {
                // OK, we are oversized!
                defragged.push_back(File(curr_free.start_posn, curr_file.size, curr_file.id));
                ull free_after = curr_free.size - curr_file.size;
                ull free_start_posn = curr_free.start_posn + curr_file.size;
                was_frees.insert(was_frees.begin(), Free(free_start_posn, free_after));
            }
        }

        if (was_files.size() > 0)
        {
            for (File f : was_files)
            {
                defragged.push_back(f);
            }
        }

        return Disk(std::vector<Free>(), defragged);
    }

    const ull Disk::checksum() const
    {
        ull checksum = 0;
        for (File f : files)
        {
            for (ull posn = f.start_posn; posn <= f.start_posn + f.size - 1; posn++)
            {
                checksum += (posn * f.id);
            }
        }
        return checksum;
    }
}