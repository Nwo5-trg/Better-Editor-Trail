#pragma once

namespace Trail {
    void startMove(PlayerObject* player, PlayerButton click);
    void endMove(PlayerObject* player, PlayerButton release);
    void startTrail();
    void stopTrail();
    void toggleTrail(bool on);
}
