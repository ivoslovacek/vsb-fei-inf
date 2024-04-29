import xmlrpc.client
import random
import visualizer
import xml.etree.ElementTree as ET


class Agent:

    def __init__(self, filename):
        # TODO 1     - load data from the XML configuration file (filename is in the parameter)
        # TODO 2     - create instance variables (login, data, visualizer, gameserver)
        # login      - load from XML file (tag 'login')
        # data       - an empty list, where data from server will be stored
        # visualizer - instance of the visuzlizer.Visualizer class
        # gameserver - connect to the remote XML-RPC server (url is provided in the XML file, tag 'url')
        # TODO 3     - call method 'add_player' on the server with login as the parameter (use instance variable 'self.login')
        xml = ET.parse(filename)
        xml_root = xml.getroot()
        self.login = ''
        self.hostname = ''

        for child in xml_root:
            if child.tag == 'login':
                self.login = child.text
            elif child.tag == 'url':
                self.hostname = child.text
                print(self.hostname)

        self.data = []
        self.visualizer = visualizer.Visualizer()
        self.gameserver = xmlrpc.client.ServerProxy(self.hostname)
        self.gameserver.add_player(self.login)
        self.data = self.gameserver.make_action(self.login, 'look', '')

    def action(self):
        # TODO 4 - Call 'make_action' method on the XML-RPC server.
        # The method has 3 parameters (login, action_name, parameters).
        # All three parameters are strings. Call the 'look' method on the server,
        # to take a look around the player, without NY parameter (empty string).
        # Every action returns a list of strings, where each row represents one
        # row from the surrounding area of the player.
        # Each string is 11-characters in length and there are 22 rows.
        # First 11 elements of the list represent the agent's environment
        # and other 11 elements of his surroundings
        # (so far, only "p" character is present to represent other agents).
        # The player is in this surrounding at the position [5][5] (5th row, 5th character).
        # Objects on the same position can be sought at the coordinates [5 + 11] [5].
        # "~" water
        # " " grass
        # "*" road
        # "t" tree
        # "o" rock (wall)
        # "f" tiled floor
        # "p" player
        self.data = self.gameserver.make_action(self.login, 'look', '')
        self.visualizer.visualize(self.data)

    def __repr__(self):
        # TODO 5 - Returns human readable representation of stored data form 'self.data' variable.
        new_line = '\n'
        return f"{new_line.join([str(row) for row in self.data])}"

    def save_data(self):
        # TODO 6 - Store data into the 'data.txt' filename.
        with open('data.txt', 'w') as file:
            file.write(str(self))


class AgentRandom(Agent):
    # TODO 7 - This agent will extend from the previous agent and
    # reimplement (override) the 'action' method so that the action will be 'move' and
    # the passed parameter will be one the directions: 'north', 'west', 'south', 'east'.
    # These directions will be randomly selected
    # (find the appropriate method from the random package).
    def action(self):
        directions = ['north', 'west', 'south', 'east']
        current_direction = directions[random.randint(0, 3)]
        if current_direction == 'north' and self.data[4][5] in [' ', '*']:
            self.gameserver.make_action(
                self.login, 'move', current_direction)
        elif current_direction == 'west' and self.data[5][4] in [' ', '*']:
            self.gameserver.make_action(
                self.login, 'move', current_direction)
        elif current_direction == 'south' and self.data[6][5] in [' ', '*']:
            self.gameserver.make_action(
                self.login, 'move', current_direction)
        elif current_direction == 'east' and self.data[5][6] in [' ', '*']:
            self.gameserver.make_action(
                self.login, 'move', current_direction)

        self.data = self.gameserver.make_action(self.login, 'look', '')
        self.visualizer.visualize(self.data)


class AgentLeftRight(Agent):
    # TODO 8 - This agent will be moving just to the left until it hits a barrier.
    # Then it rurn to the right and moves until it hits the barrier again.
    # It repeats such behavior.
    def __init__(self, filename):
        self.direction_left = True
        Agent.__init__(self, filename)

    def action(self):
        if self.direction_left is True:
            if self.data[5][4] in [' ', '*']:
                self.gameserver.make_action(self.login, 'move', 'west')
            else:
                self.direction_left = False
        else:
            if self.data[5][6] in [' ', '*']:
                self.gameserver.make_action(self.login, 'move', 'east')
            else:
                self.direction_left = True

        self.data = self.gameserver.make_action(self.login, 'look', '')
        self.visualizer.visualize(self.data)


def main():
    agent = None
    try:
        # agent = Agent('config.xml')
        agent = AgentRandom('config.xml')
        # agent = AgentLeftRight('config.xml')
        while agent.visualizer.running:
            agent.action()
            print(agent)
        else:
            agent.gameserver.make_action(agent.login, 'exit', '')

        agent.save_data()
    except KeyboardInterrupt:
        agent.gameserver.make_action(agent.login, 'exit', '')


if __name__ == '__main__':
    main()
