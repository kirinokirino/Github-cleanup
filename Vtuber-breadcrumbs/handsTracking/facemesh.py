import cv2
import mediapipe as mp
import time

capture = cv2.VideoCapture(0)

mp_draw = mp.solutions.drawing_utils
mp_face_mesh = mp.solutions.face_mesh
face_mesh = mp_face_mesh.FaceMesh(
    min_detection_confidence=0.7, min_tracking_confidence=0.3)
draw_spec = mp_draw.DrawingSpec(thickness=1, circle_radius=0)

previous_time = 0
current_time = 0
contours = None

counter = 50
while counter > 0:
    counter = counter - 1
    success, image = capture.read()
    image_rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

    image.flags.writeable = False
    results = face_mesh.process(image_rgb)
    image.flags.writeable = True

    face = results.multi_face_landmarks
    if face:
        mp_draw.draw_landmarks(
            image, face[0], mp_face_mesh.FACEMESH_CONTOURS, draw_spec, draw_spec)
        contours = mp_face_mesh.FACEMESH_CONTOURS

    current_time = time.time()
    fps = 1/(current_time-previous_time)
    previous_time = current_time

    # print(fps)

    cv2.imshow("Image", image)
    cv2.waitKey(1)

print(contours)
