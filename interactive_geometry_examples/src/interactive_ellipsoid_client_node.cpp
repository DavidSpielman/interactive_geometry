#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <interactive_geometry_msgs/action/interactive_ellipsoid.hpp>
#include <ament_index_cpp/get_package_share_directory.hpp>

int main (int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("ellipsoid_client");
  auto action_client = rclcpp_action::create_client<interactive_geometry_msgs::action::InteractiveEllipsoid>(node, "interactive_ellipsoid_server_node");

  // wait for the action server to start
  RCLCPP_INFO(node->get_logger(), "Waiting for action server to start.");
  action_client->wait_for_action_server();
  RCLCPP_INFO(node->get_logger(), "Action server started, sending goal.");

  // Fill goal
  interactive_geometry_msgs::action::InteractiveEllipsoid_Goal goal;
  goal.num_pts = 20;
  goal.mesh_link = "mesh_frame";
  goal.parent_link = "world";
  std::string path = ament_index_cpp::get_package_share_directory("interactive_geometry_examples");
  goal.results_directory  = path;

  // Send goal
  auto goal_handle_future = action_client->async_send_goal(goal);
  if (rclcpp::spin_until_future_complete(node, goal_handle_future) !=
      rclcpp::FutureReturnCode::SUCCESS)
  {
      RCLCPP_ERROR(node->get_logger(), "send goal call failed :(");
      return 1;
  }

  rclcpp_action::ClientGoalHandle<interactive_geometry_msgs::action::InteractiveEllipsoid>::SharedPtr goal_handle = goal_handle_future.get();
  if (!goal_handle) {
      RCLCPP_ERROR(node->get_logger(), "Goal was rejected by server");
      return 1;
  }

  // Wait for the server to be done with the goal
  auto result_future = action_client->async_get_result(goal_handle);

  RCLCPP_INFO(node->get_logger(), "Waiting for result");
  if (rclcpp::spin_until_future_complete(node, result_future) !=
      rclcpp::FutureReturnCode::SUCCESS)
  {
      RCLCPP_ERROR(node->get_logger(), "get result call failed :(");
      return 1;
  }

  rclcpp_action::ClientGoalHandle<interactive_geometry_msgs::action::InteractiveEllipsoid>::WrappedResult wrapped_result = result_future.get();

  switch (wrapped_result.code) {
  case rclcpp_action::ResultCode::SUCCEEDED:
      break;
  case rclcpp_action::ResultCode::ABORTED:
      RCLCPP_ERROR(node->get_logger(), "Goal was aborted");
      return 1;
  case rclcpp_action::ResultCode::CANCELED:
      RCLCPP_ERROR(node->get_logger(), "Goal was canceled");
      return 1;
  default:
      RCLCPP_ERROR(node->get_logger(), "Unknown result code");
      return 1;
  }

  RCLCPP_INFO(node->get_logger(), "result received");
  RCLCPP_INFO_STREAM(node->get_logger(), wrapped_result.result->results_path);
  rclcpp::shutdown();
  return 0;
}
