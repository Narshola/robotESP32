/*
 * File:          radio_test.c
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
#include <webots/receiver.h>
#include <webots/emitter.h>
/*
 * You may want to add macros here.
 */
#define TIME_STEP 64

/*
 * This is the main program.
 * The arguments of the main function can be specified by the
 * "controllerArgs" field of the Robot node
 */
int main(int argc, char **argv) {
  /* necessary to initialize webots stuff */
  wb_robot_init();

  WbDeviceTag receiver = wb_robot_get_device("receiver");
  wb_receiver_enable(receiver, TIME_STEP);
  
  WbDeviceTag emitter = wb_robot_get_device("emitter");
  wb_emitter_set_channel(emitter, 1);
  
  double tmr = 0;
  
  while (wb_robot_step(TIME_STEP) != -1) {
    // Радио
    // 1) Передача данных
    int msg = 1;
    if (wb_robot_get_time() - tmr > 1.0) {
      wb_emitter_send(emitter, &msg, sizeof(msg));
      tmr = wb_robot_get_time();
    }
    
    // 2) Приём данных
    // while (wb_receiver_get_queue_length(receiver) > 0) {
      // int *data_receiver = wb_receiver_get_data(receiver);
      // printf("ROBOT -> RADIO_TEST: %i\n", *data_receiver);
      // wb_receiver_next_packet(receiver);
  // };

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}
