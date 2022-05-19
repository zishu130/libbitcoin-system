/**
 * Copyright (c) 2011-2019 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef LIBBITCOIN_SYSTEM_CONFIG_INPUT_HPP
#define LIBBITCOIN_SYSTEM_CONFIG_INPUT_HPP

#include <iostream>
#include <string>
#include <bitcoin/system/chain/chain.hpp>
#include <bitcoin/system/define.hpp>

namespace libbitcoin {
namespace system {
namespace config {

/// Serialization helper stub for chain::input.
class BC_API input
{
public:
    input() noexcept;
    input(const input& other) noexcept;
    input(const chain::input& value) noexcept;
    input(const chain::point& value) noexcept;
    input(const std::string& tuple) noexcept(false);

    operator const chain::input&() const noexcept;

    friend std::istream& operator>>(std::istream& stream,
        input& argument) noexcept(false);
    friend std::ostream& operator<<(std::ostream& output,
        const input& argument) noexcept;

private:
    chain::input value_;
};

} // namespace explorer
} // namespace system
} // namespace libbitcoin

#endif
