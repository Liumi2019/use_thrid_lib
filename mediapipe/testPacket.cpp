#include "testPacket.h"
#include "degbugInclude.h"
#include <string>

namespace mediapipe {

    void testPacket() {
        Packet packet = Adopt(new int(100));
        auto re = packet.At(50).Get<int>();
        std::cout << re << std::endl;
        {
             Packet packet3 = packet.At(50);
        }
        absl::StatusOr<std::unique_ptr<int>> result1 = packet.Consume<int>();
        if (result1.ok()) {
            printMessage("mediapipe", std::string("sucess ") + std::to_string(*result1.value()));
        }

        Packet packet2 = Adopt(new int(100));
        Packet packet3 = std::move(packet2).At(50);
        absl::StatusOr<std::unique_ptr<int>> result2 = packet3.Consume<int>();
        if (result2.ok()) {
            std::cout << "sucess " << packet3.getTimestamp() << std::endl;
        }
    }
}