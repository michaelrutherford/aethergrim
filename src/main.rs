mod entity;

use crate::entity::entity::Entity;

fn main() {
    let mut player = Entity {
        x: 0,
        y: 0,
        //color: String::from("Red"),
        tile: '@',
    };

    println!("Player tile = {}", player.tile);
    println!("Player (x, y) = ({}, {})", player.x, player.y);

    println!("\nTransforming...\n");
    player.change_location(5, 2);
    player.change_tile('a');

    println!("Player tile = {}", player.tile);
    println!("Player (x, y) = ({}, {})", player.x, player.y);
}
