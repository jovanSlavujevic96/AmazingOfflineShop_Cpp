#include <iostream>

#include "Discounts.h"

#define DISCOUNTS_NUM_OF_COLS 2
#define EAN13_LEN 13

bool Discount::operator==(const Discount& other) const
{
    return this->discountPercent == other.discountPercent;
}

void Discounts::operator<<(std::shared_ptr<IFileReader> reader) noexcept(false)
{
    Discount* item;
    uint64_t key;

    // clear map
    mDiscounts.clear();

    // pass expected number of columns
    reader->setNumOfCols(DISCOUNTS_NUM_OF_COLS);

    // lambda expression
    auto validateEan13 = [](const std::string& to_validate, std::string& error)
    {
        if (to_validate.length() != EAN13_LEN)
        {
            error = "EAN13 shall be 13 digits long.";
            return false;
        }
        return true;
    };

    // row reading loop
    while (reader->read())
    {
        // read EAN-13
        key = reader->extractULongLong(validateEan13);

        // insert map element with EAN-13 key
        item = &mDiscounts.insert(std::make_pair(key, Discount())).first->second;

        // read discount percentage
        item->discountPercent = reader->extractFloat();
    }
}

const char* Discounts::getObjectType() const
{
    return "Discounts";
}
