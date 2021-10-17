import cv2
import mediapipe as mp
import time
import moderngl
from renderer import Renderer

OFFSET = [-0.01, -0.01, 0.01, -0.01, 0.0, 0.01]
COLOUR = [0.2, 0.2, 0.6]
capture = cv2.VideoCapture(0)

config_text = """
# MediaPipe graph that performs iris tracking on desktop with TensorFlow Lite
# on CPU.
# Used in the example in
# mediapipie/examples/desktop/iris_tracking:iris_tracking_cpu.

# CPU image. (ImageFrame)
input_stream: "input_video"

# CPU image. (ImageFrame)
output_stream: "output_video"
# Face landmarks with iris. (NormalizedLandmarkList)
output_stream: "face_landmarks_with_iris"

# Defines how many faces to detect. Iris tracking currently only handles one
# face (left and right eye), and therefore this should always be set to 1.
node {
  calculator: "ConstantSidePacketCalculator"
  output_side_packet: "PACKET:0:num_faces"
  node_options: {
    [type.googleapis.com/mediapipe.ConstantSidePacketCalculatorOptions]: {
      packet { int_value: 1 }
    }
  }
}

# Detects faces and corresponding landmarks.
node {
  calculator: "FaceLandmarkFrontCpu"
  input_stream: "IMAGE:input_video"
  input_side_packet: "NUM_FACES:num_faces"
  output_stream: "LANDMARKS:multi_face_landmarks"
  output_stream: "ROIS_FROM_LANDMARKS:face_rects_from_landmarks"
  output_stream: "DETECTIONS:face_detections"
  output_stream: "ROIS_FROM_DETECTIONS:face_rects_from_detections"
}

# Gets the very first and only face from "multi_face_landmarks" vector.
node {
  calculator: "SplitNormalizedLandmarkListVectorCalculator"
  input_stream: "multi_face_landmarks"
  output_stream: "face_landmarks"
  node_options: {
    [type.googleapis.com/mediapipe.SplitVectorCalculatorOptions] {
      ranges: { begin: 0 end: 1 }
      element_only: true
    }
  }
}

# Gets the very first and only face rect from "face_rects_from_landmarks"
# vector.
node {
  calculator: "SplitNormalizedRectVectorCalculator"
  input_stream: "face_rects_from_landmarks"
  output_stream: "face_rect"
  node_options: {
    [type.googleapis.com/mediapipe.SplitVectorCalculatorOptions] {
      ranges: { begin: 0 end: 1 }
      element_only: true
    }
  }
}

# Gets two landmarks which define left eye boundary.
node {
  calculator: "SplitNormalizedLandmarkListCalculator"
  input_stream: "face_landmarks"
  output_stream: "left_eye_boundary_landmarks"
  node_options: {
    [type.googleapis.com/mediapipe.SplitVectorCalculatorOptions] {
      ranges: { begin: 33 end: 34 }
      ranges: { begin: 133 end: 134 }
      combine_outputs: true
    }
  }
}

# Gets two landmarks which define right eye boundary.
node {
  calculator: "SplitNormalizedLandmarkListCalculator"
  input_stream: "face_landmarks"
  output_stream: "right_eye_boundary_landmarks"
  node_options: {
    [type.googleapis.com/mediapipe.SplitVectorCalculatorOptions] {
      ranges: { begin: 362 end: 363 }
      ranges: { begin: 263 end: 264 }
      combine_outputs: true
    }
  }
}

# Detects iris landmarks, eye contour landmarks, and corresponding rect (ROI).
node {
  calculator: "IrisLandmarkLeftAndRightCpu"
  input_stream: "IMAGE:input_video"
  input_stream: "LEFT_EYE_BOUNDARY_LANDMARKS:left_eye_boundary_landmarks"
  input_stream: "RIGHT_EYE_BOUNDARY_LANDMARKS:right_eye_boundary_landmarks"
  output_stream: "LEFT_EYE_CONTOUR_LANDMARKS:left_eye_contour_landmarks"
  output_stream: "LEFT_EYE_IRIS_LANDMARKS:left_iris_landmarks"
  output_stream: "LEFT_EYE_ROI:left_eye_rect_from_landmarks"
  output_stream: "RIGHT_EYE_CONTOUR_LANDMARKS:right_eye_contour_landmarks"
  output_stream: "RIGHT_EYE_IRIS_LANDMARKS:right_iris_landmarks"
  output_stream: "RIGHT_EYE_ROI:right_eye_rect_from_landmarks"
}

node {
  calculator: "ConcatenateNormalizedLandmarkListCalculator"
  input_stream: "left_eye_contour_landmarks"
  input_stream: "right_eye_contour_landmarks"
  output_stream: "refined_eye_landmarks"
}

node {
  calculator: "UpdateFaceLandmarksCalculator"
  input_stream: "NEW_EYE_LANDMARKS:refined_eye_landmarks"
  input_stream: "FACE_LANDMARKS:face_landmarks"
  output_stream: "UPDATED_FACE_LANDMARKS:updated_face_landmarks"
}

node {
  calculator: "ConcatenateNormalizedLandmarkListCalculator"
  input_stream: "updated_face_landmarks"
  input_stream: "iris_landmarks"
  output_stream: "face_landmarks_with_iris"
}
"""

ctx = moderngl.create_context(standalone=True)
renderer = Renderer(ctx)


def landmark_callback(packet, list):
    landmarks = mp.packet_getter.get_proto_list(packet)
    if landmarks:
        list.clear()
        vertices = []
        for idx, landmark in enumerate(landmarks[0].landmark):
            x = landmark.x * 2 - 1.0
            y = landmark.y * 2 - 1.0
            vertices.extend((x + OFFSET[0], y + OFFSET[1], COLOUR[0], COLOUR[1], COLOUR[2],
                            x + OFFSET[2], y +
                            OFFSET[3], COLOUR[0], COLOUR[1], COLOUR[2],
                            x + OFFSET[4], y + OFFSET[5], COLOUR[0], COLOUR[1], COLOUR[2]))
        list.append(vertices)


new_vertices = []


graph = mp.CalculatorGraph(graph_config=config_text)
graph.observe_output_stream(
    'face_landmarks_with_iris',
    lambda stream_name, packet:
        landmark_callback(packet, new_vertices)
)

previous_time = 0
current_time = 0
contours = None

counter = 70000
while counter > 0:
    counter = counter - 1
    graph.start_run()
    success, image = capture.read()
    image.flags.writeable = False
    image_rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

    image_rgb.flags.writeable = False

    graph.add_packet_to_input_stream(
        'input_video',
        mp.packet_creator.create_image_frame(image_format=mp.ImageFormat.SRGB,
                                             data=image_rgb).at(1))

    #face = results.multi_face_landmarks
    # if face:
    #    mp_draw.draw_landmarks(image, face[0], mp_face_mesh.FACEMESH_CONTOURS, draw_spec, draw_spec)
    #    contours = mp_face_mesh.FACEMESH_CONTOURS

    current_time = time.time()
    fps = 1/(current_time-previous_time)
    previous_time = current_time

    print(fps)
    if len(new_vertices) > 0:
        renderer.update_vertices(ctx, new_vertices)
    cv2.imshow("Image", renderer.image())
    cv2.waitKey(1)

    graph.close()
