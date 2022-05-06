from abc import ABC, abstractmethod

class bot_abstract(ABC):
    @abstractmethod
    def get_name(self):
        pass

    @abstractmethod
    def get_move(self, board, parameters):
        pass