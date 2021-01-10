//
// Created by florian on 09.01.21.
//

#include "chessman_factory.h"
#include "chesspiece/chessman_type.h"
#include "chesspiece/chessman.h"
#include "chesspiece/king.h"
#include "chesspiece/queen.h"
#include "chesspiece/bishop.h"
#include "chesspiece/knight.h"
#include "chesspiece/rook.h"
#include "chesspiece/pawn.h"

namespace chess {
  chessman_factory::chessman_factory(color c) : c{c} {}

  chessman *chessman_factory::produce_chessman(chessman_type type) const {
    switch (type) {
      case chessman_type::king:
        return new king(this->c);
      case chessman_type::queen:
        return new queen(this->c);
      case chessman_type::bishop:
        return new bishop(this->c);
      case chessman_type::knight:
        return new knight(this->c);
      case chessman_type::rook:
        return new rook(this->c);
      case chessman_type::pawn:
        return new pawn(this->c);
    }
  }
}