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
#include "../test.hpp"
#include <string>

BOOST_AUTO_TEST_SUITE(string_tests)

// data

BOOST_AUTO_TEST_CASE(string__ascii_space__always__expected)
{
    BOOST_REQUIRE_EQUAL(ascii_space.size(), 1u);
    BOOST_REQUIRE_EQUAL(ascii_space[0], ' ');
}

BOOST_AUTO_TEST_CASE(string__separators__always__expected)
{
    BOOST_REQUIRE_EQUAL(ascii_separators.size(), 1u);
    BOOST_REQUIRE_EQUAL(ascii_separators[0][0], ' ');
}

BOOST_AUTO_TEST_CASE(string__whitespace__always__expected)
{
    BOOST_REQUIRE_EQUAL(ascii_whitespace.size(), 6u);
    BOOST_REQUIRE_EQUAL(ascii_whitespace[0][0], '\t');
    BOOST_REQUIRE_EQUAL(ascii_whitespace[1][0], '\n');
    BOOST_REQUIRE_EQUAL(ascii_whitespace[2][0], '\v');
    BOOST_REQUIRE_EQUAL(ascii_whitespace[3][0], '\f');
    BOOST_REQUIRE_EQUAL(ascii_whitespace[4][0], '\r');
    BOOST_REQUIRE_EQUAL(ascii_whitespace[5][0], ' ');
}

// ascii_to_lower

BOOST_AUTO_TEST_CASE(string__ascii_to_lower__empty__empty)
{
    const std::string value{ "" };
    BOOST_REQUIRE_EQUAL(ascii_to_lower(value), value);
}

BOOST_AUTO_TEST_CASE(string__ascii_to_lower__lower__unchanged)
{
    const std::string value{ "abcdefghijklmnopqrstuvwxyz0123456789" };
    BOOST_REQUIRE_EQUAL(ascii_to_lower(value), value);
}

BOOST_AUTO_TEST_CASE(string__ascii_to_lower__upper__lowered)
{
    const std::string value{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" };
    const std::string expected{ "abcdefghijklmnopqrstuvwxyz0123456789" };
    BOOST_REQUIRE_EQUAL(ascii_to_lower(value), expected);
}

BOOST_AUTO_TEST_CASE(string__ascii_to_lower__mixed__lowered)
{
    const std::string value{ "AbCdEfGhIjKlMnOpQrStUvWxYz0123456789" };
    const std::string expected{ "abcdefghijklmnopqrstuvwxyz0123456789" };
    BOOST_REQUIRE_EQUAL(ascii_to_lower(value), expected);
}

// ascii_to_upper

BOOST_AUTO_TEST_CASE(string__ascii_to_upper__empty__empty)
{
    const std::string value{ "" };
    BOOST_REQUIRE_EQUAL(ascii_to_upper(value), value);
}

BOOST_AUTO_TEST_CASE(string__ascii_to_upper__lower__raised)
{
    const std::string value{ "abcdefghijklmnopqrstuvwxyz0123456789" };
    const std::string expected{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" };
    BOOST_REQUIRE_EQUAL(ascii_to_upper(value), expected);
}

BOOST_AUTO_TEST_CASE(string__ascii_to_upper__upper__unchanged)
{
    const std::string value{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" };
    BOOST_REQUIRE_EQUAL(ascii_to_upper(value), value);
}

BOOST_AUTO_TEST_CASE(string__ascii_to_upper__mixed__raised)
{
    const std::string value{ "AbCdEfGhIjKlMnOpQrStUvWxYz0123456789" };
    const std::string expected{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" };
    BOOST_REQUIRE_EQUAL(ascii_to_upper(value), expected);
}

// has_mixed_ascii_case

BOOST_AUTO_TEST_CASE(string__has_mixed_ascii_case__empty__false)
{
    BOOST_REQUIRE(!has_mixed_ascii_case(""));
}

BOOST_AUTO_TEST_CASE(string__has_mixed_ascii_case__mixed_case_with_non_ascii__true)
{
    BOOST_REQUIRE(has_mixed_ascii_case("\x80xYz"));
}

BOOST_AUTO_TEST_CASE(string__has_mixed_ascii_case__lower__false)
{
    BOOST_REQUIRE(!has_mixed_ascii_case("abcdefghijklmnopqrstuvwxyz0123456789"));
}

BOOST_AUTO_TEST_CASE(string__has_mixed_ascii_case__upper__false)
{
    BOOST_REQUIRE(!has_mixed_ascii_case("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"));
}

BOOST_AUTO_TEST_CASE(string__has_mixed_ascii_case__mixed__true)
{
    BOOST_REQUIRE(has_mixed_ascii_case("AbCdEfGhIjKlMnOpQrStUvWxYz0123456789"));
}

// is_ascii

BOOST_AUTO_TEST_CASE(string__is_ascii__empty__true)
{
    BOOST_REQUIRE(is_ascii(""));
}

BOOST_AUTO_TEST_CASE(string__is_ascii__alphanumeric__true)
{
    BOOST_REQUIRE(is_ascii("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"));
}

BOOST_AUTO_TEST_CASE(string__is_ascii__below_128__true)
{
    BOOST_REQUIRE(is_ascii(std::string{ '\x00' }));
    BOOST_REQUIRE(is_ascii(std::string{ '\x7f' }));
}

BOOST_AUTO_TEST_CASE(string__is_ascii__above_127__false)
{
    BOOST_REQUIRE(!is_ascii(std::string{ '\x80' }));
    BOOST_REQUIRE(!is_ascii(std::string{ '\xff' }));
}

// join

BOOST_AUTO_TEST_CASE(string__join1__empties__one_space)
{
    BOOST_REQUIRE_EQUAL(system::join(string_list{ "", "" }), " ");
}

BOOST_AUTO_TEST_CASE(string__join1__spaces__three_spaces)
{
    BOOST_REQUIRE_EQUAL(system::join(string_list{ " ", " " }, " "), "   ");
}

BOOST_AUTO_TEST_CASE(string__join1__left_value__right_space)
{
    BOOST_REQUIRE_EQUAL(system::join(string_list{ "a", "" }), "a ");
}

BOOST_AUTO_TEST_CASE(string__join1__right_value__left_space)
{
    BOOST_REQUIRE_EQUAL(system::join(string_list{ "", "b" }), " b");
}

BOOST_AUTO_TEST_CASE(string__join1__values__delimited)
{
    BOOST_REQUIRE_EQUAL(system::join(string_list{ "abc", "xyz" }), "abc xyz");
}

BOOST_AUTO_TEST_CASE(string__join2__empties_empty_delimiter__empty)
{
    BOOST_REQUIRE_EQUAL(system::join(string_list{ "", "" }, ""), "");
}

BOOST_AUTO_TEST_CASE(string__join2__values_empty_delimiter__undelimited)
{
    BOOST_REQUIRE_EQUAL(system::join(string_list{ "abc", "xyz" }, ""), "abcxyz");
}

BOOST_AUTO_TEST_CASE(string__join2__values_comma_delimiter__delimited)
{
    BOOST_REQUIRE_EQUAL(system::join(string_list{ "abc", "xyz" }, ","), "abc,xyz");
}

BOOST_AUTO_TEST_CASE(string__join2__values_ideographic_space_delimiter__delimited)
{
    BOOST_REQUIRE_EQUAL(system::join(string_list{ "abc", "xyz" }, ideographic_space), "abc\xe3\x80\x80xyz");
}

BOOST_AUTO_TEST_CASE(string__join2__untrimmed_values_comma_delimiter__untrimmed_delimited)
{
    BOOST_REQUIRE_EQUAL(system::join(string_list{ " abc ", " xyz " }, ","), " abc , xyz ");
}

// reduce

BOOST_AUTO_TEST_CASE(string__reduce__empty__empty)
{
    string_list values{};
    const string_list expected{};
    reduce(values);
    BOOST_REQUIRE_EQUAL(values, expected);
}

BOOST_AUTO_TEST_CASE(string__reduce__nothing_to_do__unchanged)
{
    string_list values{ "a", "b", "c" };
    const string_list expected{ "a", "b", "c" };
    reduce(values);
    BOOST_REQUIRE_EQUAL(values, expected);
}

BOOST_AUTO_TEST_CASE(string__reduce__empties__single_empty)
{
    string_list values{ "", "", "" };
    const string_list expected{ "" };
    reduce(values);
    BOOST_REQUIRE_EQUAL(values, expected);
}

BOOST_AUTO_TEST_CASE(string__reduce__whitespace__trimmed)
{
    string_list values{ " \ta\t ", "\r\tb\t\n", "\t\tc\t\t" };
    const string_list expected{ "a", "b", "c" };
    reduce(values);
    BOOST_REQUIRE_EQUAL(values, expected);
}

BOOST_AUTO_TEST_CASE(string__reduce__only_whitespace__trimmed_and_reduced)
{
    string_list values{ " \t\t ", "\r\t\t\n", "\t\tc\t\t" };
    const string_list expected{ "c" };
    reduce(values);
    BOOST_REQUIRE_EQUAL(values, expected);
}

BOOST_AUTO_TEST_CASE(string__reduce__empties_reduce_false__unchanged)
{
    string_list values{ "", "", "" };
    const string_list expected = values;
    reduce(values, true, false);
    BOOST_REQUIRE_EQUAL(values, expected);
}

BOOST_AUTO_TEST_CASE(string__reduce__padded_trim_false__unchanged)
{
    string_list values{ " \ta\t ", "\r\tb\t\n", "\t\tc\t\t" };
    const string_list expected = values;
    reduce(values, false, true);
    BOOST_REQUIRE_EQUAL(values, expected);
}

BOOST_AUTO_TEST_CASE(string__reduce__only_whitespace_both_false__unchanged)
{
    string_list values{ " \t\t ", "\r\t\t\n", "\t\tc\t\t" };
    const string_list expected = values;
    reduce(values, false, false);
    BOOST_REQUIRE_EQUAL(values, expected);
}

// replace

BOOST_AUTO_TEST_CASE(string__replace__empty__empty)
{
    std::string value{};
    const std::string expected{};
    BOOST_REQUIRE_EQUAL(replace(value, "def", "klm"), 0u);
    BOOST_REQUIRE_EQUAL(value, expected);
}

BOOST_AUTO_TEST_CASE(string__replace__none__unchanged)
{
    std::string value{ "abc xyz abc xyz" };
    BOOST_REQUIRE_EQUAL(replace(value, "def", "klm"), 0u);
    BOOST_REQUIRE_EQUAL(value, value);
}

BOOST_AUTO_TEST_CASE(string__replace__multiple__expected)
{
    std::string value{ "abc def abc def" };
    const std::string expected{ "abc klm abc klm" };
    BOOST_REQUIRE_EQUAL(replace(value, "def", "klm"), 2u);
    BOOST_REQUIRE_EQUAL(value, expected);
}

BOOST_AUTO_TEST_CASE(string__replace__multiple_adjacent__expected)
{
    std::string value{ "defdefabcdef" };
    const std::string expected{ "klmklmabcklm" };
    BOOST_REQUIRE_EQUAL(replace(value, "def", "klm"), 3u);
    BOOST_REQUIRE_EQUAL(value, expected);
}

BOOST_AUTO_TEST_CASE(string__replace__shorter__expected)
{
    std::string value{ "abc def abc def" };
    const std::string expected{ "abc kl abc kl" };
    BOOST_REQUIRE_EQUAL(replace(value, "def", "kl"), 2u);
    BOOST_REQUIRE_EQUAL(value, expected);
}

BOOST_AUTO_TEST_CASE(string__replace__longer__expected)
{
    std::string value{ "abc def abc def" };
    const std::string expected{ "abc klmn abc klmn" };
    BOOST_REQUIRE_EQUAL(replace(value, "def", "klmn"), 2u);
    BOOST_REQUIRE_EQUAL(value, expected);
}

BOOST_AUTO_TEST_CASE(string__replace__reflexive__expected)
{
    std::string value{ "abc def abc def" };
    const std::string expected{ "abc defdef abc defdef" };
    BOOST_REQUIRE_EQUAL(replace(value, "def", "defdef"), 2u);
    BOOST_REQUIRE_EQUAL(value, expected);
}

BOOST_AUTO_TEST_CASE(string__replace__with_spaces__expected)
{
    std::string value{ "abc def abc def" };
    const std::string expected1{ " bc def  bc def" };
    BOOST_REQUIRE_EQUAL(replace(value, "a", " "), 2u);
    BOOST_REQUIRE_EQUAL(value, expected1);
    const std::string expected2{ "  c def   c def" };
    BOOST_REQUIRE_EQUAL(replace(value, "b", " "), 2u);
    BOOST_REQUIRE_EQUAL(value, expected2);
    const std::string expected3{ "    def     def" };
    BOOST_REQUIRE_EQUAL(replace(value, "c", " "), 2u);
    BOOST_REQUIRE_EQUAL(value, expected3);
    const string_list expected4{ "", "", "", "", "def", "", "", "", "", "def" };
    BOOST_REQUIRE_EQUAL(split(value, false, false), expected4);
}

// split

BOOST_AUTO_TEST_CASE(string__split0__compress__untrimmed)
{
    const std::string value{ "\t\r\n abc " };
    const string_list expected{ "\t\r\n", "abc" };
    BOOST_REQUIRE_EQUAL(system::split(value, false), expected);
}

BOOST_AUTO_TEST_CASE(string__split0__trim___uncompressed)
{
    const std::string value{ " abc \t\r\n" };
    const string_list expected{ "", "abc", "" };
    BOOST_REQUIRE_EQUAL(system::split(value, true, false), expected);
}

BOOST_AUTO_TEST_CASE(string__split1__empty__empty)
{
    const std::string value{};
    const string_list expected{ "" };
    BOOST_REQUIRE_EQUAL(system::split(value), expected);
}

BOOST_AUTO_TEST_CASE(string__split1__empty_token__empty_token)
{
    const std::string value{ "" };
    const string_list expected{ value };
    BOOST_REQUIRE_EQUAL(system::split(value), expected);
}

BOOST_AUTO_TEST_CASE(string__split1__no_delimiter__one_token)
{
    const std::string value{ "abc" };
    const string_list expected{ value };
    BOOST_REQUIRE_EQUAL(system::split(value), expected);
}

BOOST_AUTO_TEST_CASE(string__split1__one_delimiter__split)
{
    const std::string value{ "abc xyz" };
    const string_list expected{ "abc", "xyz" };
    BOOST_REQUIRE_EQUAL(system::split(value), expected);
}

BOOST_AUTO_TEST_CASE(string__split1__nine_delimiters__compressed)
{
    const std::string value{ "abc   xyz   123   456" };
    const string_list expected{ "abc", "xyz", "123", "456" };
    BOOST_REQUIRE_EQUAL(system::split(value), expected);
}

BOOST_AUTO_TEST_CASE(string__split1__one_delimiter__left_trimmed_and_compressed)
{
    const std::string value{ "\t\r\n abc" };
    const string_list expected{ "abc" };
    BOOST_REQUIRE_EQUAL(system::split(value), expected);
}

BOOST_AUTO_TEST_CASE(string__split1__one_delimiter___right_trimmed_and_compressed)
{
    const std::string value{ "abc \t\r\n" };
    const string_list expected{ "abc" };
    BOOST_REQUIRE_EQUAL(system::split(value), expected);
}

BOOST_AUTO_TEST_CASE(string__split1__twelve_delimiters__trimmed_and_compressed)
{
    const std::string value{ "  \t\r\n  abc  \t\r\n  xyz  \t\r\n  " };
    const string_list expected{ "abc", "xyz" };
    BOOST_REQUIRE_EQUAL(system::split(value), expected);
}

BOOST_AUTO_TEST_CASE(string__split2__one_ideographic_space_delimiter__split)
{
    const std::string value{ "www\xe3\x80\x80mmm" };
    const string_list expected{ "www", "mmm" };
    BOOST_REQUIRE_EQUAL(system::split(value, ideographic_space), expected);
}

BOOST_AUTO_TEST_CASE(string__split2__three_ideographic_space_delimiters__compressed)
{
    const std::string value{ "\xe3\x80\x80www\xe3\x80\x80mmm\xe3\x80\x80" };
    const string_list expected{ "www", "mmm" };
    BOOST_REQUIRE_EQUAL(system::split(value, ideographic_space), expected);
}

BOOST_AUTO_TEST_CASE(string__split2__four_ideographic_space_delimiters__trimmed_compressed)
{
    const std::string value{ " \xe3\x80\x80 www \xe3\x80\x80\xe3\x80\x80 mmm \xe3\x80\x80 " };
    const string_list expected{ "www", "mmm" };
    BOOST_REQUIRE_EQUAL(system::split(value, ideographic_space), expected);
}

BOOST_AUTO_TEST_CASE(string__split3__one_delimiter__untrimmed)
{
    const std::string value{ "\t\r\n abc" };
    const string_list expected{ "\t\r\n", "abc" };
    BOOST_REQUIRE_EQUAL(system::split(value, ascii_space, false), expected);
}

BOOST_AUTO_TEST_CASE(string__split3__one_delimiter___untrimmed)
{
    const std::string value{ "abc \t\r\n" };
    const string_list expected{ "abc", "\t\r\n" };
    BOOST_REQUIRE_EQUAL(system::split(value, ascii_space, false), expected);
}

BOOST_AUTO_TEST_CASE(string__split3__twelve_delimiters__untrimmed_compressed)
{
    const std::string value{ "  \t\r\n  abc  \t\r\n  xyz  \t\r\n  " };
    const string_list expected{ "\t\r\n", "abc", "\t\r\n", "xyz", "\t\r\n" };
    BOOST_REQUIRE_EQUAL(system::split(value, ascii_space, false), expected);
}

BOOST_AUTO_TEST_CASE(string__split3__four_ideographic_space_delimiters__untrimmed_compressed)
{
    const std::string value{ " \xe3\x80\x80 www \xe3\x80\x80\xe3\x80\x80 mmm \xe3\x80\x80 " };
    const string_list expected{ " ", " www ", " mmm ", " " };
    BOOST_REQUIRE_EQUAL(system::split(value, ideographic_space, false), expected);
}

BOOST_AUTO_TEST_CASE(string__split4__twelve_comma_delimiters__trimmed_uncompressed)
{
    const std::string value{ ",,\t\r\n,,abc,,\t\r\n,,xyz,,\t\r\n,," };
    const string_list expected{ "", "", "", "", "abc", "", "", "", "xyz", "", "", "", "" };
    BOOST_REQUIRE_EQUAL(system::split(value, ",", true, false), expected);
}

BOOST_AUTO_TEST_CASE(string__split4__four_ideographic_space_delimiters__untrimmed_uncompressed)
{
    const std::string value{ " \xe3\x80\x80 www \xe3\x80\x80\xe3\x80\x80 mmm \xe3\x80\x80 " };
    const string_list expected{ " ", " www ", "", " mmm ", " " };
    BOOST_REQUIRE_EQUAL(system::split(value, ideographic_space, false, false), expected);
}

BOOST_AUTO_TEST_CASE(string__split5__ascii_and_ideographic_space_delimiters__untrimmed_uncompressed)
{
    const std::string value{ "\t \xe3\x80\x80 www \xe3\x80\x80\xe3\x80\x80 mmm \xe3\x80\x80 \t" };
    const string_list expected{ "\t", "", "", "www", "", "", "", "mmm", "", "", "\t" };
    const string_list delimiters{ ideographic_space, ascii_space };
    BOOST_REQUIRE_EQUAL(system::split(value, delimiters, false, false), expected);
}

BOOST_AUTO_TEST_CASE(string__split5__ascii_and_ideographic_space_delimiters__untrimmed_compressed)
{
    const std::string value{ "\t \xe3\x80\x80 www \xe3\x80\x80\xe3\x80\x80 mmm \xe3\x80\x80 \t" };
    const string_list expected{ "\t", "www", "mmm", "\t" };
    const string_list delimiters{ ideographic_space, ascii_space };
    BOOST_REQUIRE_EQUAL(system::split(value, delimiters, false), expected);
}

BOOST_AUTO_TEST_CASE(string__split5__alpha_bravo_charlie__compressed)
{
    const std::string value{ "alpha bravo charlie" };
    const string_list expected{ "lph", "r", "vo", "h", "rlie" };
    const string_list delimiters{ "a", "b", "c", " " };
    BOOST_REQUIRE_EQUAL(system::split(value, delimiters, false, true), expected);
}

BOOST_AUTO_TEST_CASE(string__split5__alpha_bravo_charlie__trimmed)
{
    const std::string value{ "\talpha \tbravo\t charlie\t" };
    const string_list expected{ "", "lph", "", "", "r", "vo", "", "h", "rlie" };
    const string_list delimiters{ "a", "b", "c", " " };
    BOOST_REQUIRE_EQUAL(system::split(value, delimiters, true, false), expected);
}

// starts_with

BOOST_AUTO_TEST_CASE(string__starts_with__empty_empty__true)
{
    BOOST_REQUIRE(system::starts_with("", ""));
}

BOOST_AUTO_TEST_CASE(string__starts_with__ending__false)
{
    BOOST_REQUIRE(!system::starts_with("abc", "bc"));
}

BOOST_AUTO_TEST_CASE(string__starts_with__overflow__false)
{
    BOOST_REQUIRE(!system::starts_with("abc", "abcd"));
}

BOOST_AUTO_TEST_CASE(string__starts_with__found__true)
{
    BOOST_REQUIRE(system::starts_with("abc", "ab"));
}

// to_string

BOOST_AUTO_TEST_CASE(string__to_string__empty__empty)
{
    const data_chunk value{};
    const std::string expected{ "" };
    BOOST_REQUIRE_EQUAL(to_string(value), expected);
}

BOOST_AUTO_TEST_CASE(string__to_string__vector__expected)
{
    const data_chunk value{ 'a', 'b', 'c' };
    const std::string expected{ "abc" };
    BOOST_REQUIRE_EQUAL(to_string(value), expected);
}

BOOST_AUTO_TEST_CASE(string__to_string__array__expected)
{
    const byte_array<3> value{ { 'a', 'b', 'c' } };
    const std::string expected{ "abc" };
    BOOST_REQUIRE_EQUAL(system::to_string(value), expected);
}

// trim

BOOST_AUTO_TEST_CASE(string__trim__empty__empty)
{
    std::string value{ "" };
    system::trim(value);
    BOOST_REQUIRE_EQUAL(value, "");
}

BOOST_AUTO_TEST_CASE(string__trim___all_whitespace__empty)
{
    std::string value{ " \t\n\v\f\r " };
    system::trim(value);
    BOOST_REQUIRE_EQUAL(value, "");
}

BOOST_AUTO_TEST_CASE(string__trim__internal_whitespace__unchanged)
{
    std::string value{ "1 \t\n\v\f\r 1" };
    const auto expected = value;
    system::trim(value);
    BOOST_REQUIRE_EQUAL(value, expected);
}

BOOST_AUTO_TEST_CASE(string__trim__external_whitespace__trimmed)
{
    std::string value{ "\t\n\v\f\r 1 \r\f\v\n\t" };
    system::trim(value);
    BOOST_REQUIRE_EQUAL(value, "1");
}

// trim_copy

BOOST_AUTO_TEST_CASE(string__trim_copy__empty__empty)
{
    BOOST_REQUIRE_EQUAL(system::trim_copy(""), "");
}

BOOST_AUTO_TEST_CASE(string__trim_copy__all_whitespace__empty)
{
    BOOST_REQUIRE_EQUAL(system::trim_copy(" \t\n\v\f\r "), "");
}

BOOST_AUTO_TEST_CASE(string__trim_copy__internal_whitespace__unchanged)
{
    BOOST_REQUIRE_EQUAL(system::trim_copy("1 \t\n\v\f\r 1"), "1 \t\n\v\f\r 1");
}

BOOST_AUTO_TEST_CASE(string__trim_copy__external_whitespace__trimmed)
{
    BOOST_REQUIRE_EQUAL(system::trim_copy("\t\n\v\f\r 1 \r\f\v\n\t"), "1");
}

BOOST_AUTO_TEST_SUITE_END()
