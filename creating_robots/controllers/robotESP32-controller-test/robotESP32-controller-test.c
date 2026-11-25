/*
 * File:          robotESP32-controller-test.c
 * Date:
 * Description:
 * Author:
 * Modifications:
 */

/*
 * You may need to add include files like <webots/distance_sensor.h> or
 * <webots/motor.h>, etc.
 */
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/accelerometer.h>
#include <webots/gyro.h>
#include <webots/distance_sensor.h>
#include <webots/compass.h>
#include <webots/emitter.h>
#include <webots/receiver.h>
#include <webots/keyboard.h>

#include <stdio.h>

#define TIME_STEP 64

int main(int argc, char **argv) {
  /* necessary to initialize webots stuff */
  
  wb_robot_init();
    
  WbDeviceTag wheels[4];
  // 0 (wheel1) - Левый передний мотор
  // 1 - Левый задний мотор
  // 2 - Правый передний мотор
  // 3 - Правый задний мотор
  char wheels_names[4][8] = {"wheel1", "wheel2", "wheel3", "wheel4"};
  for (int i = 0; i < 4; i++) {
    wheels[i] = wb_robot_get_device(wheels_names[i]);
    wb_motor_set_position(wheels[i], INFINITY);
  }
  
  WbDeviceTag accel = wb_robot_get_device("accelerometer");
  wb_accelerometer_enable(accel, TIME_STEP);
  
  WbDeviceTag gyro = wb_robot_get_device("gyro");
  wb_gyro_enable(gyro, TIME_STEP);
  
  WbDeviceTag forward_ds = wb_robot_get_device("forward_ds");
  wb_distance_sensor_enable(forward_ds, TIME_STEP);
  
  WbDeviceTag back_ds = wb_robot_get_device("back_ds");
  wb_distance_sensor_enable(back_ds, TIME_STEP);
  
  WbDeviceTag compass = wb_robot_get_device("compass");
  wb_compass_enable(compass, TIME_STEP);
  
  WbDeviceTag receiver = wb_robot_get_device("receiver");
  wb_receiver_enable(receiver, TIME_STEP);
  
  WbDeviceTag emitter = wb_robot_get_device("emitter");
  wb_emitter_set_channel(emitter, 1);
  
  wb_keyboard_enable(TIME_STEP);
  
  //Для отправки сообщения раз в секунду
  double tmr = 0;
  
  while (wb_robot_step(TIME_STEP) != -1) {
    double left_speed = 0;
    double right_speed = 0;
    
    int key = wb_keyboard_get_key();
    if (key == WB_KEYBOARD_UP) {
      left_speed = 3.0;
      right_speed = 3.0;
    }
    else if (key == WB_KEYBOARD_DOWN) {
      left_speed = -3.0;
      right_speed = -3.0;
    }
    else if (key == WB_KEYBOARD_LEFT) {
      left_speed = -2.5;
      right_speed = 2.5;
    }
    else if (key == WB_KEYBOARD_RIGHT) {
      left_speed = 2.5;
      right_speed = -2.5;
    }
    
    wb_motor_set_velocity(wheels[0], left_speed);
    wb_motor_set_velocity(wheels[1], left_speed);
    wb_motor_set_velocity(wheels[2], right_speed);
    wb_motor_set_velocity(wheels[3], right_speed);
    
    
    // Акселерометр
    // X - ускорение вдоль ОX и т. д.
    // const double *data_accel = wb_accelerometer_get_values(accel);
    // printf("accelerometer data: X=%.2f, Y=%.2f, Z=%.2f\n", data_accel[0], data_accel[1], data_accel[2]);
    
    
    // Датчики расстояния
    // const double data_fds = wb_distance_sensor_get_value(forward_ds);
    // printf("forward distance sensor data: %.2f\n", data_fds); 
    // const double data_bds = wb_distance_sensor_get_value(back_ds);
    // printf("back distance sensor data: %.2f\n", data_bds);
    
    
    // Компас
    // X - направление на север по OX и т.д..
    // const double *data_compass = wb_compass_get_values(compass);
    // printf("compass data: X=%.2f Y=%.2f Z=%.2f\n", data_compass[0], data_compass[1], data_compass[2]);
    
    
    // Гироскопический датчик
    // X - крен, Y - тангаж, Z - рыскание
    // const double *data_gyro = wb_gyro_get_values(gyro);
    // printf("gyro data: X=%.2f Y=%.2f Z=%.2f\n", data_gyro[0], data_gyro[1], data_gyro[2]);
    
    
    // Радио (?)
    // 1) Передача данных
    // int msg = 1;
    // if (wb_robot_get_time() - tmr > 1.0) {
      // wb_emitter_send(emitter, &msg, sizeof(msg));
      // tmr = wb_robot_get_time();
    // }
    
    // 2) Приём данных
    // printf("%d\n", wb_receiver_get_queue_length(receiver));
    // while (wb_receiver_get_queue_length(receiver) > 0) {
      // int *data_receiver = wb_receiver_get_data(receiver);
      // printf("RADIO_TEST -> ROBOT: %i\n", *data_receiver);
      // wb_receiver_next_packet(receiver);
    // }
    
    
    fflush(stdout);

  };

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}