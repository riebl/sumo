/****************************************************************************/
/// @file    NBLinkCliqueContainer.h
/// @author  Daniel Krajzewicz
/// @date    Sept 2002
/// @version $Id$
///
// A container for link cliques
/****************************************************************************/
// SUMO, Simulation of Urban MObility; see http://sumo.sourceforge.net/
// copyright : (C) 2001-2007
//  by DLR (http://www.dlr.de/) and ZAIK (http://www.zaik.uni-koeln.de/AFS)
/****************************************************************************/
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
//
/****************************************************************************/
#ifndef NBLinkCliqueContainer_h
#define NBLinkCliqueContainer_h


// ===========================================================================
// included modules
// ===========================================================================
#ifdef _MSC_VER
#include <windows_config.h>
#else
#include <config.h>
#endif

#include <vector>
#include <bitset>
#include "NBLinkPossibilityMatrix.h"
#include "NBTrafficLightPhases.h"


// ===========================================================================
// class definitions
// ===========================================================================
/**
 * @class NBLinkCliqueContainer
 * This container stores linkcliques. A link clique is a set of links of a
 * junction that may be used parallel, that means, that none of the links
 * within such a clique is a foe to another one from the same clique.
 * For a faster computation of permutations of the cliques that do regard all
 * links, a second structure, _further,  also stores the information which
 * links are regarded within the following cliques (the sizes of _cliques
 * and _further are the same)
 */
class NBLinkCliqueContainer
{
public:
    /// constructor
    NBLinkCliqueContainer(NBLinkPossibilityMatrix *v,
                          size_t maxStromAnz);

    /// destructor
    ~NBLinkCliqueContainer();

    /** computes all possible phase combinations that regard all links
        of the junction */
    NBTrafficLightPhases *computePhases(NBLinkPossibilityMatrix *v,
                                        size_t noLinks, bool appendSmallestOnly, bool skipLarger) const;

    /** Tests whether the item at the given position is set.
    The position is given by the clique index and the index within this
        clique */
    bool test(size_t itemIndex, size_t linkIndex) const;

private:
    /// builds the possible cliques
    void buildCliques(NBLinkPossibilityMatrix *v, size_t maxStromAnz);

    /// builds the information which links are set in further steps
    void buildFurther();

    /** returns the information whether all links are regarded when
        a certain list of regarded links and the position within the clique
        vector is given */
    bool furtherResolutionPossible(std::bitset<64> vorhanden,
                                   std::bitset<64> needed, size_t next) const;

private:
    /// the definitions of the list of cliques
    typedef std::vector<std::bitset<64> > LinkCliqueContainer;

    /// the list of cliques
    LinkCliqueContainer _cliques;

    /// the definitions of the list of further set cliques
    typedef std::vector<std::bitset<64> > FurtherPossibleContainer;

    /// the list of further set cliques
    FurtherPossibleContainer _further;
};


#endif

/****************************************************************************/

