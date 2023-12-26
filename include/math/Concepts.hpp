//
// Created by Toni on 23/12/2023.
//

#ifndef RUPE_CONCEPTS_HPP
#define RUPE_CONCEPTS_HPP

namespace Rupe::Math::Concepts {

    /// Checks if a non-narrowing conversion is possible
    /// \tparam From The type to convert from
    /// \tparam To The type to convert to
    template <typename From, typename To>
    concept NonNarrowingConversion = requires(From f) { To{f}; };

}

#endif //RUPE_CONCEPTS_HPP
