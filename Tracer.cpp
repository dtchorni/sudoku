//
// Created by dtchorni on 30/06/19.
//

#include "Tracer.hpp"
#include "Arguments.hpp"


std::vector<Tile > FIFOtrace::traceBack(int *i) {
    std::vector<Tile> removed;
    for(int steps=0; steps< args.stepbacks; ++steps) {
        Tile t = game->getFirstTile();
        game->findAndRemoveNumber(t.x, t.y, t.val, 0);
        removed.push_back(t);
    }
    return removed;
}

std::vector<Tile> LIFOtrace::traceBack(int *i) {
    std::vector<Tile> removed;
    for(int steps=0; steps<args.stepbacks; ++steps) {
        int ind = game->totalTiles() - 1;
        Tile t = game->getLastTile();
        game->findAndRemoveNumber(t.x, t.y, t.val, ind);
        removed.insert(removed.begin(),t);
    }
    return removed;
}

std::vector<Tile> MatchNumberTrace::traceBack(int *val) {
    std::vector<Tile> removed;
    for(int ind=0; ind<game->totalTiles()-1 && removed.size() < args.stepbacks; ++ind){
        Tile t = game->getTileAt(ind);
        if(*val == t.val) {
            game->findAndRemoveNumber(t.x,t.y,t.val,ind);
            removed.push_back(t);
            ind--;
        }
    }
    return removed;
}
