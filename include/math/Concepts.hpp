//
// Created by Toni on 23/12/2023.
//

#ifndef RUPE_CONCEPTS_HPP
#define RUPE_CONCEPTS_HPP

// TODO: Document
namespace Rupe::Math::Concepts {
    template <typename From, typename To>
    concept NonNarrowingConversion = requires(From f) { To{f}; };
}

#endif //RUPE_CONCEPTS_HPP
