from abc import ABC, abstractmethod

# Class repsenting checkers bot.
# All subclasses must be added to bot_manager or they will be unusable.
# Only one instance of a subclass can be created.
class bot_abstract(ABC):
    @abstractmethod
    def get_name(self):
        pass

    @abstractmethod
    def get_move(self, board, parameters):
        pass