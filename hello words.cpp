//////////////////////////////// bai 1 ////////////////////////
#include <iostream>
#include <string>

struct FileNode {
    std::string fileName;
    long fileSize; // kích thước file tính bằng byte
    FileNode* next;
};

// Thêm file vào danh sách theo thứ tự kích thước
void insertFile(FileNode*& head, const std::string& fileName, long fileSize) {
    FileNode* newFile = new FileNode{ fileName, fileSize, nullptr };
    if (!head || head->fileSize > fileSize) {
        newFile->next = head;
        head = newFile;
    }
    else {
        FileNode* current = head;
        while (current->next && current->next->fileSize <= fileSize) {
            current = current->next;
        }
        newFile->next = current->next;
        current->next = newFile;
    }
}

// Tính tổng kích thước file trong danh sách
long calculateTotalSize(FileNode* head) {
    long totalSize = 0;
    while (head) {
        totalSize += head->fileSize;
        head = head->next;
    }
    return totalSize;
}

// Xóa file kích thước nhỏ nhất cho đến khi tổng kích thước <= 32GB
void removeSmallestFiles(FileNode*& head, long maxSize) {
    while (head && calculateTotalSize(head) > maxSize) {
        FileNode* temp = head;
        head = head->next;
        delete temp;
    }
}

// In danh sách file
void printFiles(FileNode* head) {
    while (head) {
        std::cout << "File Name: " << head->fileName << ", Size: " << head->fileSize << " bytes" << std::endl;
        head = head->next;
    }
}

int main() {
    FileNode* fileList = nullptr;

    // Thêm các file ví dụ vào danh sách
    insertFile(fileList, "file1.txt", 15000000); // 15MB
    insertFile(fileList, "file2.txt", 80000000); // 80MB
    insertFile(fileList, "file3.txt", 2000000); // 2MB
    insertFile(fileList, "file4.txt", 50000000); // 50MB

    std::cout << "File list before backup:" << std::endl;
    printFiles(fileList);

    long maxUSBSize = 32 * 1024 * 1024 * 1024; // 32 GB in bytes
    removeSmallestFiles(fileList, maxUSBSize);

    std::cout << "File list after removing small files to fit in 32GB:" << std::endl;
    printFiles(fileList);

    // Giải phóng bộ nhớ
    while (fileList) {
        FileNode* temp = fileList;
        fileList = fileList->next;
        delete temp;
    }

    return 0;
}


////////////////////////////bai 2 /////////////////////////

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

struct WordNode {
    std::string word;
    WordNode* next;
};

// Thêm một từ vào danh sách
void insertWord(WordNode*& head, const std::string& word) {
    WordNode* newWord = new WordNode{ word, head };
    head = newWord;
}

// Đếm số từ và tìm từ xuất hiện nhiều nhất
void analyzeWords(WordNode* head) {
    std::unordered_map<std::string, int> wordCount;
    WordNode* current = head;

    while (current) {
        wordCount[current->word]++;
        current = current->next;
    }

    // Tìm từ xuất hiện nhiều nhất
    std::string mostFrequentWord;
    int maxCount = 0;
    for (const auto& pair : wordCount) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            mostFrequentWord = pair.first;
        }
    }

    // Kiểm tra từ láy
    for (const auto& pair : wordCount) {
        if (pair.first.length() > 1 && pair.first[0] == pair.first[1]) {
            std::cout << "Found reduplicated word: " << pair.first << ". Removing one occurrence." << std::endl;
            wordCount[pair.first]--;
        }
    }

    // Đếm số từ
    int totalWords = wordCount.size();
    std::cout << "Most frequent word: " << mostFrequentWord << " with " << maxCount << " occurrences." << std::endl;
    std::cout << "Total unique words: " << totalWords << std::endl;
}

int main() {
    WordNode* wordList = nullptr;

    // Ví dụ câu
    std::string sentence = "xanh xanh red blue blue green yellow blue";
    std::string word;

    std::istringstream stream(sentence);
    while (stream >> word) {
        insertWord(wordList, word);
    }

    analyzeWords(wordList);

    // Giải phóng bộ nhớ
    while (wordList) {
        WordNode* temp = wordList;
        wordList = wordList->next;
        delete temp;
    }

    return 0;
}
