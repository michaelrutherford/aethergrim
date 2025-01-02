pub mod entity {
    pub struct Entity {
        pub x: u16,
        pub y: u16,
        //pub color: String,
        pub tile: char,
    }

    impl Entity {
        pub fn change_location(&mut self, new_x: u16, new_y: u16) {
            self.x = new_x;
            self.y = new_y;
        }
        pub fn change_tile(&mut self, new_tile: char) {
            self.tile = new_tile;
        }
    }
}
