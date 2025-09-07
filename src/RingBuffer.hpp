#include <iostream>
#include <array>
#include <string>
#include <mutex>
#include <optional>

template <size_t BufferSize>
class RingBuffer {
private:
    std::array<char, BufferSize> buffer;
    size_t head = 0; // 書き込み位置
    size_t tail = 0; // 読み取り位置
    bool full = false; // バッファが満杯かどうか
public:
    // データをバッファに追加
    void push(char data) {
        buffer[head] = data;
        head = (head + 1) % BufferSize;

        if (full) {
            tail = (tail + 1) % BufferSize; // 上書き時は読み取り位置を進める
        }

        full = (head == tail);
    }

    // バッファからデータを取り出す（FIFO）
    std::optional<char> pop() {
        if (isEmpty()) {
            return std::nullopt; // バッファが空の場合
        }

        char data = buffer[tail];
        tail = (tail + 1) % BufferSize;
        full = false;

        return data;
    }

    // バッファが空かどうか
    bool isEmpty() const {
        return (!full && (head == tail));
    }

    // バッファ内のデータ数を取得
    size_t size() const {
        if (full) {
            return BufferSize;
        }
        if (head >= tail) {
            return head - tail;
        } else {
            return BufferSize + head - tail;
        }
    }

    // バッファ内のデータを文字列として取得（デバッグ用）
    std::string dump() {
        std::string result;
        size_t index = tail;
        while (index != head) {
            result += buffer[index];
            index = (index + 1) % BufferSize;
        }
        return result;
    }
};

// SSとEEで囲まれたデータを抽出する関数
std::optional<std::string> extractMessage(RingBuffer<256>& ringBuffer) {
    static std::string tempBuffer;
    while (!ringBuffer.isEmpty()) {
        auto data = ringBuffer.pop();
        if (!data.has_value()) break;

        tempBuffer += data.value();

        // "SS"で始まるデータの検索
        size_t start = tempBuffer.find("SS");
        if (start != std::string::npos) {
            // "EE"で終わるデータの検索
            size_t end = tempBuffer.find("EE", start);
            if (end != std::string::npos) {
                // メッセージを抽出
                std::string message = tempBuffer.substr(start + 2, end - start - 2);
                tempBuffer.erase(0, end + 2); // 使用済みデータを削除
                return message;
            }
        }

        // バッファが長くなりすぎないように管理
        if (tempBuffer.size() > 512) {
            tempBuffer.erase(0, tempBuffer.size() - 512);
        }
    }
    return std::nullopt;
}

