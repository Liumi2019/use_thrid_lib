// Copyright 2019 The MediaPipe Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "packet.h"

#include "absl/strings/str_cat.h"

namespace mediapipe {
namespace packet_internal {

HolderBase::~HolderBase() {}

Packet Create(HolderBase* holder) {
  Packet result;
  result.holder_.reset(holder);
  return result;
}

Packet Create(HolderBase* holder, Timestamp timestamp) {
  Packet result;
  result.holder_.reset(holder);
  result.timestamp_ = timestamp;
  return result;
}

Packet Create(std::shared_ptr<HolderBase> holder, Timestamp timestamp) {
  Packet result;
  result.holder_ = std::move(holder);
  result.timestamp_ = timestamp;
  return result;
}

const HolderBase* GetHolder(const Packet& packet) {
  return packet.holder_.get();
}

}  // namespace packet_internal

Packet Packet::At(Timestamp timestamp) const& {
  Packet result(*this);
  result.timestamp_ = timestamp;
  return result;
}

Packet Packet::At(Timestamp timestamp) && {
  timestamp_ = timestamp;
  // Note: Below object is of type Packet&& which doesn't match return type
  // of Packet, so a new Packet will be created by move constructor here.
  // Moving everything to a new Packet is done intentionally to preserve the
  // immutability of Timestamps.
  return std::move(*this);
}

std::string Packet::RegisteredTypeName() const {
  if (IsEmpty()) {
    return "";
  }
  return holder_->RegisteredTypeName();
}

std::string Packet::DebugTypeName() const {
  if (IsEmpty()) {
    return "{empty}";
  }
  return holder_->DebugTypeName();
}

std::string Packet::DebugString() const {
  std::string result = absl::StrCat("mediapipe::Packet with timestamp: ",
                                    std::to_string(timestamp_));
  if (IsEmpty()) {
    absl::StrAppend(&result, " and no data");
  } else {
    absl::StrAppend(&result, " and type: ", holder_->DebugTypeName());
  }
  return result;
}

}  // namespace mediapipe
