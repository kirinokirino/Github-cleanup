import cv2
import mediapipe as mp 
import time

capture = cv2.VideoCapture(0)

mp_hands = mp.solutions.hands
mp_draw = mp.solutions.drawing_utils

static_image_mode = False # If True, uses only detection without tracking, slower
max_num_hands = 2
min_detection_confidence = 0.7
min_tracking_confidence = 0.3

hands = mp_hands.Hands(static_image_mode, max_num_hands, min_detection_confidence, min_tracking_confidence)

previous_time = 0
current_time = 0

while True:
    success, image = capture.read()
    image_rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    result = hands.process(image_rgb)

    if result.multi_hand_landmarks:
        for hand_landmarks in result.multi_hand_landmarks:
            mp_draw.draw_landmarks(image, hand_landmarks, mp_hands.HAND_CONNECTIONS)

    current_time = time.time()
    fps = 1/(current_time-previous_time)
    previous_time = current_time

    print(fps)

    cv2.imshow("Image", image)
    cv2.waitKey(1)