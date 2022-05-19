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
#include <bitcoin/system/config/transaction.hpp>

#include <sstream>
#include <string>
#include <bitcoin/system/chain/transaction.hpp>
#include <bitcoin/system/config/base16.hpp>
#include <bitcoin/system/exceptions.hpp>

namespace libbitcoin {
namespace system {
namespace config {

using namespace boost::program_options;

transaction::transaction() noexcept
  : value_()
{
}

transaction::transaction(const chain::transaction& value) noexcept
  : value_(value)
{
}

transaction::transaction(const transaction& other) noexcept
  : transaction(other.value_)
{
}

transaction::transaction(const std::string& hexcode) noexcept(false)
{
    std::stringstream(hexcode) >> *this;
}

chain::transaction& transaction::data() noexcept
{
    return value_;
}

transaction::operator const chain::transaction&() const noexcept
{
    return value_;
}

std::istream& operator>>(std::istream& input,
    transaction& argument) noexcept(false)
{
    std::string hexcode;
    input >> hexcode;

    argument.value_ = chain::transaction{ base16(hexcode), true };

    if (!argument.value_.is_valid())
        throw istream_exception(hexcode);

    return input;
}

std::ostream& operator<<(std::ostream& output,
    const transaction& argument) noexcept
{
    output << base16(argument.value_.to_data(true));
    return output;
}

} // namespace config
} // namespace system
} // namespace libbitcoin
