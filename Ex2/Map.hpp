//
//  Map.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 14/11/2015.
//  Copyright © 2015 Bar-Ilan. All rights reserved.
//

#ifndef Map_hpp
#define Map_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include "Tile.hpp"

class Map {

    ///The width of the map
    size_t m_uiWidth;
    
    ///The height of the map
    size_t m_uiHeight;
    
    ///Holds the Tiles that make up the map
    Tile** m_cData;
    
    /**
     * Unsafe method to get the index of a coordiante.
     *
     * @param x The X coordinate for the requested index.
     * @param y The Y coordinate for the requested index.
     * @return The index of the input coordinate.
     */
    size_t index(size_t x, size_t y) const;
    
    /**
     * Returns the neighbors of the input tile.
     *
     * @param cTile The Tile we want to get the neighbors of.
     * @return A vector containing pointers to all of the input Tile's neighbors.
     */
    const std::vector<const Tile*> getNeighbors(const Tile& cTile) const;
        
public:
    
    /**
     * Constructor.
     *
     * @param strFormattedMap A formatted string that represents a map.
     */
    Map(const std::string& strFormattedMap);
    
    /**
     * Copy Constructor.
     *
     * @param The map to be copied.
     */
    Map(const Map& cMap);
    
    /** 
     * Destructor.
     */
    ~Map();
    
    /**
     * Returns the Tile that is marked as the start location in the map.
     * 
     * @return The Starting tile.
     */
    Tile getStartTile() const;
    
    /**
     * Returns the Tile that is marked as the end location in the map.
     *
     * @return The End tile.
     */
    Tile getEndTile() const;
    
    /**
     * Returns the tile count of the map.
     * 
     * @return Number of tiles in the map.
     */
    size_t getTilesCount() const;
    
    /**
     * Returns the index in the map for an input tile.
     *
     * @param cTile The Tile we want to know the index of.
     * @return The index of the input tile.
     */
    size_t getIndex(const Tile& cTile) const;
    
    /**
     * Returns the index for the input coordiante.
     * Throws exception if the coordiante is not valid.
     * 
     * @param uiX The X coordinate.
     * @param uiY The Y coordinate.
     * @return The index for the input coordinate.
     */
    size_t getIndex(size_t uiX, size_t uiY) const throw(...);
    
    /** May return null if out of map bounds */
    const Tile* getTile(const Tile& cOrigin, Directions direction) const;
    
};

#endif /* Map_hpp */
