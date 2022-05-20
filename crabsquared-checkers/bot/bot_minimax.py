import math
from ..engine.python import engine
from .bot_abstract import bot_abstract

MINIMAX_DEPTH = 9

def reward(board, color):
  pawn_val = 1
  king_val = 10

  flat_board = [char for row in board for char in row]
  whites = flat_board.count('w') * pawn_val + flat_board.count('W') * king_val
  blacks = flat_board.count('b') * pawn_val + flat_board.count('B') * king_val

  return blacks - whites if color == 1 else whites - blacks

def minimax(board, depth, alpha, beta, color):
  moves = engine.valid_moves(board, color)
  if depth == 0 or not moves:
    return None, reward(board, color)
  
  best_move = None

  if color == 1:
    best_reward = -math.inf
  else:
    best_reward = math.inf

  for move in [mv for (_, group) in moves.items() for mv in group]:
    child_board = engine.get_board_after_move(board, move)
    _, child_reward = minimax(child_board, depth - 1, alpha, beta, 1 - color)
    if color == 1 and child_reward > best_reward:
      best_reward = child_reward
      best_move = move
      alpha = max(alpha, child_reward)
    elif color == 0 and child_reward < best_reward:
      best_reward = child_reward
      best_move = move
      beta = min(beta, child_reward)
    if beta <= alpha:
        break
  assert best_move is not None
  return best_move, best_reward


class bot_minimax(bot_abstract):
    def get_name(self):
        return 'bot_minimax'

    def get_move(self, board, parameters = {}):
      alpha, beta = -math.inf, math.inf
      move, _ = minimax(board, MINIMAX_DEPTH, alpha, beta, 1)
      return move

