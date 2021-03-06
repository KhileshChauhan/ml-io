/*
 * Copyright 2019-2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You
 * may not use this file except in compliance with the License. A copy of
 * the License is located at
 *
 *      http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is
 * distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF
 * ANY KIND, either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 */

#pragma once

#include <cstddef>

#include "mlio/config.h"
#include "mlio/intrusive_ref_counter.h"

namespace mlio {
inline namespace abi_v1 {

/// @addtogroup memory Memory
/// @{

class MLIO_API Memory_block : public Intrusive_ref_counter<Memory_block> {
public:
    using value_type = std::byte;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = const std::byte &;
    using const_reference = const std::byte &;
    using pointer = const std::byte *;
    using const_pointer = const std::byte *;
    using iterator = const std::byte *;
    using const_iterator = const std::byte *;

    Memory_block() noexcept = default;

    Memory_block(const Memory_block &) = delete;

    Memory_block &operator=(const Memory_block &) = delete;

    Memory_block(Memory_block &&) = delete;

    Memory_block &operator=(Memory_block &&) = delete;

    virtual ~Memory_block();

    const_iterator begin() const noexcept
    {
        return data();
    }

    const_iterator end() const noexcept
    {
        return data() + size();
    }

    const_iterator cbegin() const noexcept
    {
        return begin();
    }

    const_iterator cend() const noexcept
    {
        return end();
    }

    virtual const_pointer data() const noexcept = 0;

    virtual size_type size() const noexcept = 0;
};

class MLIO_API Mutable_memory_block : public Memory_block {
public:
    using reference = std::byte &;
    using pointer = std::byte *;
    using iterator = std::byte *;

    Mutable_memory_block() noexcept = default;

    Mutable_memory_block(const Mutable_memory_block &) = delete;

    Mutable_memory_block &operator=(const Mutable_memory_block &) = delete;

    Mutable_memory_block(Mutable_memory_block &&) = delete;

    Mutable_memory_block &operator=(Mutable_memory_block &&) = delete;

    ~Mutable_memory_block() override;

    iterator begin() noexcept
    {
        return data();
    }

    iterator end() noexcept
    {
        return data() + size();
    }

    virtual void resize(size_type size) = 0;

    using Memory_block::data;

    virtual pointer data() noexcept = 0;

    virtual bool resizable() const noexcept = 0;
};

/// @}

}  // namespace abi_v1
}  // namespace mlio
