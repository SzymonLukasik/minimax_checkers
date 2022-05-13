from abc import ABC, abstractmethod

# Base class for all checkers bots.
# All bots must implement this and be added to bot_manager in order to
# allow selecting it in API.
class bot_abstract(ABC):
    # Unique name used in API requests.
    @abstractmethod
    def get_name(self):
        pass

    # Function that returns bot move based on board state.
    @abstractmethod
    def get_move(self, board, parameters):
        pass