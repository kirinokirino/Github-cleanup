#!/usr/bin/env python3

import random
import pygame
from pygame.locals import *

if not pygame.font: print('Warning, fonts disabled')
if not pygame.mixer: print('Warning, sound disabled')

class game():
  
  def __init__(self):
    self.SIZE = 800, 600
    pygame.init()
    self.screen = pygame.display.set_mode(self.SIZE)
    pygame.display.set_caption('game_test_v0.1')
    #pygame.mouse.set_visible(0)
    pygame.display.update()
    
    self.background = pygame.Surface(self.screen.get_size())
    self.background = self.background.convert()
    self.background.fill((255, 255, 255))
    self.screen.blit(self.background, (0, 0))
    
    self.clock = pygame.time.Clock()
    self.isRunning = True
    self.main_loop(self.setup())
    pygame.quit()
    
  def main_loop(self, *argv):
    while (self.isRunning):
      self.clock.tick(60)
      for event in pygame.event.get():
        if event.type == QUIT:
          self.isRunning = False
        elif event.type == KEYDOWN and event.key == K_ESCAPE:
          self.isRunning = False
        elif event.type == MOUSEBUTTONDOWN:
          pass
        elif event.type == MOUSEBUTTONUP:
          pass
      
      self.background.fill((200, 250, 250))
      self.screen.blit(self.background, (0, 0))
      for arg in argv:
        for obj in arg:    #WTH
          obj.update(self.screen)
          obj.draw(self.screen)
      pygame.display.update()
      
  def setup(self):
    #all game objects go here
    #they need to have draw and update methods
    argv = []
    argv.append(rectangle(pos = (30, 30), speed = (59, 30)))
    
    return argv
      
class game_object():
  def __init__(self):
    pass
  def update(self, screen):
    pass
  def draw(self, screen):
    pass

class rectangle(game_object):
  def __init__(self, pos = (0.0, 0.0), speed = (0.0, 0.0), acceleration = (0.0, 0.0)):
    self.color = pygame.Color(25, 150, 100)
    self.speed = speed
    self.acceleration = acceleration
    self.pos = pos
    self.drag = 0.98
    self.bouncyness = 0.3
    self.rect = pygame.Rect(self.pos[0], self.pos[1], 50, 50)
  def update(self, screen):
    x,y = self.pos
    dx, dy = self.speed
    ndx, ndy = self.acceleration
    if x < self.rect.width/2:
      x = self.rect.width/2
      dx = -dx*self.bouncyness
    elif x > screen.get_width() - self.rect.width/2:
      x = screen.get_width() - self.rect.width/2
      dx = -dx*self.bouncyness
    if y < self.rect.height/2:
      y = self.rect.height/2
      dy = -dy*self.bouncyness
    elif y > screen.get_height() - self.rect.height/2:
      y = screen.get_height() - self.rect.height/2
      dy = -dy*self.bouncyness
      
    self.pos = x+dx,y+dy
    self.speed = dx*self.drag+ndx,dy*self.drag+ndy
    self.acceleration = self.force()
    self.rect.center = self.pos[0], self.pos[1]
  def force(self):
    ndx, ndy = 0, 0
    ndx += 0 #wind
    ndy += 0 #gravity
    return ndx, ndy
  def draw(self, screen):
    pygame.draw.rect(screen, self.color, self.rect)

if __name__ == '__main__':
  Game = game()