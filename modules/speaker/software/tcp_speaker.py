#!/usr/bin/python3

from pygame import mixer
import socket, re, os, signal

################################################################################
############################### Configuration ##################################
################################################################################

BUFFER_LENGTH = 1024

################################################################################
########################### end of Configuration ###############################
################################################################################


class Server():
    def __init__(self, port):
        self.__port = port
        self.__host = '' # all interfaces
        self.__socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.__socket.bind((self.__host, self.__port))
        self.__socket.listen(5)
        
    def handleNextConnection(self):
        connection, client =self.__socket.accept()
        data = connection.recv(BUFFER_LENGTH)
        connection.sendall('OK'.encode('utf-8'))
        return data.decode("utf-8")        


class Player():
    def __init__(self, path = ""):
        self.__path = path
        self.__mixer = mixer
        self.__mixer.init()
        self.__vlc_pid = None
        self.__vlc_url = None
        
    def setPath(self, path):
        self.__path = path
        
    def play(self):
        self.__mixer.music.load(self.__path)
        self.__mixer.music.play()
        
    def stop(self):
        self.__mixer.music.stop()
    
    def pause(self):
        self.__mixer.music.pause()
        
    def resume(self):
        self.__mixer.music.unpause()
    
    def playWeb(self, url):
        if (self.__vlc_pid == None):
            self.__vlc_url = url
            self.__vlc_pid = os.fork()
            if self.__vlc_pid == 0:
                os.system("cvlc --intf dummy "+self.__vlc_url)
                os._exit(0)
        else:
            self.stopWeb()
            self.playWeb(url)
        
    def stopWeb(self):
        os.system("killall vlc -9")
        self.__vlc_pid = None


def main():
    server = Server(7708)
    player = Player("music.flac")
    while True:
        try:
            request = server.handleNextConnection()
        except Exception as e:
            pass
            
        try:
            print(request)
            play = re.match(r'/music/play/(.*)', request, re.I)
            if play:
                player.setPath(play.group(1))
                player.play()
            
            play_web = re.match(r'/music/web/play/(.*)', request, re.I)
            if play_web:
                player.playWeb(play_web.group(1))
                
            elif (request == "/music/play"):
                player.play()
                
            elif (request == "/music/pause"):
                player.pause()
                
            elif (request == "/music/resume"):
                player.resume()
                
            elif (request == "/music/stop"):
                player.stop()
            
            elif (request == "/music/web/stop"):
                player.stopWeb()
        
        except Exception as e:
            print(e)
            pass


if __name__ == "__main__":
    main()